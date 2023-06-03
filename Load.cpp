#include "Load.h"

using namespace Load;

void Obj::Read(const std::string obj_model_filepath)
{


	std::cout << "reading" << std::endl;
	using namespace std;
	ifstream file(obj_model_filepath);

	int debugCounter = 0;


	if (!file.is_open())
	{
		cout << "Error opening the file: " << obj_model_filepath << endl;
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
			for (int i = 0; i < 3; ++i)
			{
				//std :: cout << "F Counter" << debugCounter++ << std::endl;

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
			}
		}

		else if (type == "mtlib")
		{
			std::string matFileName;
			iss >> matFileName;

			Obj::ReadMaterial(matFileName);
		}
	}
	file.close();
}

void Obj::ReadMaterial(const std::string mtl_fileName)
{
	using namespace std;
	ifstream file(mtl_fileName);

	if (!file.is_open())
	{
		cout << "Error opening the file: " << mtl_fileName << endl;
		return;
	}

	string line;

	while (getline(file, line))
	{
		istringstream iss(line);
		string type;

		iss >> type;

		if (type == "ka")
		{

		}
		else if (type == "kd")
		{

		}
		else if (type == "ks")
		{

		}
		else if (type == "ns")
		{

		}
		else if (type == "map_Kd")
		{
			string texFileName;
			iss >> texFileName;
			Obj::ReadTexture(texFileName);
		}
	}
}

void Obj::ReadTexture(const std::string tex_fileName)
{

}


void Obj::Send(void)
{
	GLfloat lPositions[8064 * 3];
	GLfloat lNormals[4034 * 3];
	GLfloat lTextureCoords[4223 * 2];

	//vamos iterar por cada vertice no array de Data

	std::cout << "Number of posistions : " << positions.size() << std::endl;
	std::cout << "Number of normals : " << normals.size() << std::endl;
	std::cout << "Number of texCoords : " << texcoords.size() << std::endl;

	for (int i = 0; i < positions.size() / 3; i++) {

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

		// Upload da respetiva data para o buffer que está BIND (0);
		if (i == 0) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lPositions), lPositions, 0);

		if (i == 1) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lNormals), lNormals, 0);

		if (i == 2) glBufferStorage(GL_ARRAY_BUFFER, sizeof(lTextureCoords), lTextureCoords, 0);

	}





	//Debugging

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cout << "OpenGL Error: " << error << std::endl;
	}
}

void Obj::Draw(glm::vec3 position, glm::vec3 orientation)
{

}