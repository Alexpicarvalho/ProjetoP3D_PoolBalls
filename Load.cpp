#include "Load.h"
#include "LoadShaders.h"
#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using namespace Load;

void Obj::Read(const std::string obj_model_filepath, GLuint posId, GLuint normId, GLuint texId, GLuint textureBindId, GLuint shader, int counter)
{
	this->shaderProgram = shader;
	this->posId = posId;
	this->normId = normId;
	this->texId = texId;
	this->counter = counter;
	this->textureBindID = textureBindId;
	/*ball::Ball ballCollider;
	this->thisBall = ballCollider;*/

	std::cout << "reading" << std::endl;
	using namespace std;
	ifstream file(obj_model_filepath);

	int debugCounter = 0;


	if (!file.is_open())
	{
		std::cout << "Error opening the file: " << obj_model_filepath << endl;
		return;
	}

	std::vector<glm::vec3> tempPositions;
	std::vector<glm::vec3> tempNormals;
	std::vector<glm::vec2> tempTexcoords;

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string type;

		iss >> type;

		if (type == "v")
		{
			glm::vec3 position;
			iss >> position.x >> position.y >> position.z;
			tempPositions.push_back(position);
		}
		else if (type == "vn")
		{
			glm::vec3 normal;
			iss >> normal.x >> normal.y >> normal.z;
			tempNormals.push_back(normal);
		}
		else if (type == "vt")
		{
			glm::vec2 texcoord;
			iss >> texcoord.x >> texcoord.y;
			tempTexcoords.push_back(texcoord);
		}
		else if (type == "f")
		{
			vector<int> posIndexes;
			vector<int> texIndexes;
			vector<int> normalIndexes;
			//std::cout << "f ";
			//std :: cout << "F Counter" << debugCounter++ << std::endl;
			for (int i = 0; i < 3; ++i)
			{

				string vertexData;
				iss >> vertexData;

				istringstream viss(vertexData);
				string index;

				getline(viss, index, '/');
				int positionIndex = stoi(index) - 1;

				getline(viss, index, '/');
				int texcoordIndex = stoi(index) - 1;

				getline(viss, index, '/');
				int normalIndex = stoi(index) - 1;

				positions.push_back(tempPositions[positionIndex]);
				normals.push_back(tempNormals[normalIndex]);
				texcoords.push_back(tempTexcoords[texcoordIndex]);

				/*VertexData vertex;
				vertex.position = positions[positionIndex];
				vertex.normal = normals[normalIndex];
				vertex.texcoords = texcoords[texcoordIndex];

				vertData.push_back(vertex);*/

				//std::cout << positionIndex + 1 << "/" << texcoordIndex + 1 << "/" << normalIndex + 1 << " ";
			}
			//std::cout << endl;
		}
		if (type == "mtllib")
		{
			string mtlFileName;
			iss >> mtlFileName; // Salvar o nome do arquivo MTL
			ReadMaterial(mtlFileName);
		}
	}
	std::cout << tempPositions.size() << endl;
	std::cout << tempNormals.size() << endl;
	std::cout << tempTexcoords.size() << endl;

	std::cout << positions.size() << endl;
	std::cout << normals.size() << endl;
	std::cout << texcoords.size() << endl;
	//cout << faces.size() << endl;

	file.close();
}

void Obj::ReadMaterial(const std::string mtl_fileName)
{
	using namespace std;
	ifstream file("poolballs/" + mtl_fileName);

	if (!file.is_open())
	{
		std::cout << "Error opening the file: " << mtl_fileName << endl;
		return;
	}

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string type;

		iss >> type;

		if (type == "Ka")
		{
			iss >> ka.x >> ka.y >> ka.z;
		}
		else if (type == "Kd")
		{
			iss >> kd.x >> kd.y >> kd.z;
		}
		else if (type == "Ks")
		{
			iss >> ks.x >> ks.y >> ks.z;
		}
		else if (type == "Ns")
		{
			iss >> ns;
		}
		else if (type == "map_Kd")
		{
			string texFileName;
			iss >> texFileName;
			Obj::ReadTexture(texFileName);
		}
	}

	file.close();
}

void Obj::ReadTexture(const std::string tex_fileName)
{
	glActiveTexture(GL_TEXTURE0);

	GLuint textID = counter;
	textureID = textID;
	
	glGenTextures(1, &textID);

	glBindTexture(GL_TEXTURE_2D, textID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width, height, nChannels;

	stbi_set_flip_vertically_on_load(true);

	std::string tmpTexFile = "poolballs/" + tex_fileName;

	unsigned char* imageData = stbi_load(tmpTexFile.c_str(), &width, &height, &nChannels, 0);

	if (imageData)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
			nChannels == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, imageData);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(imageData);
	}
	else std::cout << "Error loading the texture" << std::endl;
}


void Obj::Send(void)
{
	GLfloat lPositions[8064 * 3 * 3];
	GLfloat lNormals[8064 * 3 * 3];
	GLfloat lTextureCoords[8064 * 2 * 3];

	//vamos iterar por cada vertice no array de Data

	//std::cout << "Number of posistions : " << positions.size() << std::endl;
	//std::cout << "Number of normals : " << normals.size() << std::endl;
	//std::cout << "Number of texCoords : " << texcoords.size() << std::endl;

	for (int i = 0; i < positions.size(); i++) {

		//Vertices
		lPositions[i * 3] = positions[i].x;
		lPositions[i * 3 + 1] = positions[i].y;
		lPositions[i * 3 + 2] = positions[i].z;

		//Normais
		lNormals[i * 3] = normals[i].x;
		lNormals[i * 3 + 1] = normals[i].y;
		lNormals[i * 3 + 2] = normals[i].z;

		//Coordenadas de Texture
		lTextureCoords[i * 2] = texcoords[i].x;
		lTextureCoords[i * 2 + 1] = texcoords[i].y;

		//std::cout << "Current position: " << currentPosition << std::endl;
	}

	//GL Methods, 

	glGenVertexArrays(1, &vertexArrayObject); // Geramos o VAO e retornamos o respetivo ID
	glBindVertexArray(vertexArrayObject);     // Damos bind ao VAO a partir do ID gerado
	glGenBuffers(3, vertexBufferObject);
	//Passamos os dados para os VBO's

	for (int i = 0; i < 3; i++)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[i]);

		// Upload da respetiva data para o buffer que est� BIND (0);
		if (i == 0) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lPositions), lPositions, 0);

		if (i == 1) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lNormals), lNormals, 0);

		if (i == 2) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lTextureCoords), lTextureCoords, 0);

	}
	//Debugging

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]);
	glVertexAttribPointer(posId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[1]);
	glVertexAttribPointer(normId, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[2]);
	glVertexAttribPointer(texId, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Enable nos atributos

	glEnableVertexAttribArray(posId);
	glEnableVertexAttribArray(normId);
	glEnableVertexAttribArray(texId);

	//Texture Handeling

	glProgramUniform1i(shaderProgram, textureBindID, 0);
}

/// <summary>
/// 
/// </summary>
/// <param name="position">ball pos</param>
/// <param name="orientation">ball rotation</param>
void Obj::Draw(glm::vec3 position, glm::vec3 orientation, glm::mat4 modelMatrix)
{
	using namespace glm;
	//model = glm::mat4(1.0f);
	mat4 tempModel = modelMatrix;
	currentPosition = position;

	tempModel = translate(tempModel, position);

	tempModel = rotate(tempModel, radians(orientation.x), vec3(1, 0, 0));
	tempModel = rotate(tempModel, radians(orientation.y), vec3(0, 1, 0));
	tempModel = rotate(tempModel, radians(orientation.z), vec3(0, 0, 1));

	GLint modelId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "Model");
	glProgramUniformMatrix4fv(shaderProgram, modelId, 1, GL_FALSE, value_ptr(tempModel));

	mat4 modelView = cam::Camera::GetInstance()->view * tempModel;
	GLint modelViewId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "ModelView");
	glProgramUniformMatrix4fv(shaderProgram, modelViewId, 1, GL_FALSE, value_ptr(modelView));

	mat3 normalMatrix = glm::inverseTranspose(glm::mat3(modelView));
	GLint normalMatrixId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "NormalMatrix");
	glProgramUniformMatrix4fv(shaderProgram, normalMatrixId, 1, GL_FALSE, value_ptr(normalMatrix));

	GLint viewId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "View");
	glProgramUniformMatrix4fv(shaderProgram, viewId, 1, GL_FALSE, value_ptr(cam::Camera::GetInstance()->view));

	GLint projectionId = glGetProgramResourceLocation(shaderProgram, GL_UNIFORM, "Projection");
	glProgramUniformMatrix4fv(shaderProgram, projectionId, 1, GL_FALSE, value_ptr(cam::Camera::GetInstance()->projection));

	glBindTexture(GL_TEXTURE_2D, textureID + 1);

	glBindVertexArray(vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, positions.size());
}