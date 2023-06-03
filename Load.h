#pragma once

#include <glm\glm.hpp>
#include <gl\GL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace Load {

	struct VertexData {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};

	class Obj
	{
	public:
		void Read(const std::string);
		void ReadMaterial(const std::string);
		void ReadTexture(const std::string);
		void Send(void);
		void Draw(glm::vec3, glm::vec3);
	private : 
		std::vector<VertexData> vertData;
		glm::vec3 ka, kd, ks;
		GLfloat ns;

		//buffers
		GLuint vertexArrayObject;
		GLuint vertexBufferObject[3]; // Cada tipo de data numa posição (0 = posição, 1 = normais, 2 = coordenadas da UV)
	};

	void Obj::Read(const std::string obj_model_filepath)
	{
		cout << "reading" << endl;
		using namespace std;
		ifstream file(obj_model_filepath);

		if (!file.is_open())
		{
			cout << "Error opening the file: " << obj_model_filepath << endl;
			return;
		}

		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> texcoords;

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
				positions.push_back(position);
			}
			else if (type == "vn")
			{
				glm::vec3 normal;
				iss >> normal.x >> normal.y >> normal.z;
				normals.push_back(normal);
			}
			else if (type == "vt")
			{
				glm::vec2 texcoord;
				iss >> texcoord.x >> texcoord.y;
				texcoords.push_back(texcoord);
			}
			else if (type == "f")
			{
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

					VertexData vertex;
					vertex.position = positions[positionIndex];
					vertex.normal = normals[normalIndex];
					vertex.texcoords = texcoords[texcoordIndex];

					vertData.push_back(vertex);

				}
			}
		}
	}

	void Obj::Send(void)
	{
		GLfloat vertex[4034 * 3];
		GLfloat normals[4034 * 3];
		GLfloat textureCoords[4034 * 2];

		//vamos iterar por cada vertice no array de Data

		int currentPosition = 0;

		for (VertexData vert : vertData) {

			//Vertices
			vertex[currentPosition * 3] = vert.position.x;
			vertex[currentPosition * 3 + 1] = vert.position.y;
			vertex[currentPosition * 3 + 2] = vert.position.z;

			//Normais
			normals[currentPosition * 3] = vert.normal.x;
			normals[currentPosition * 3 + 1] = vert.normal.y;
			normals[currentPosition * 3 + 2] = vert.normal.z;

			//Coordenadas de Texture
			textureCoords[currentPosition * 2] = vert.texcoords.x;
			textureCoords[currentPosition * 2 + 1] = vert.texcoords.y;

			currentPosition++;
		}

		//GL Methods, 
		glGenVertexArrays(1, &vertexArrayObject); // Geramos o VAO e retornamos o respetivo ID
		glBindVertexArray(vertexArrayObject);     // Damos bind ao VAO a partir do ID gerado
		glGenBuffers(3, vertexBufferObject);

		//

	}

	void Obj::Draw(glm::vec3 position, glm::vec3 orientation)
	{

	}
}