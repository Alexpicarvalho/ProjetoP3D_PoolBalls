#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>



#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace Load {

	/*struct VertexData {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
	};*/

	class Obj
	{
	public:
		void Read(const std::string);
		void ReadMaterial(const std::string);
		void ReadTexture(const std::string);
		void Send(void);
		void Draw(glm::vec3, glm::vec3);
		GLuint getShaderProgram();
	private : 

		//Vertex data types
		std::vector < glm::vec3> positions;
		std::vector < glm::vec3> normals;
		std::vector < glm::vec2> texcoords;

		//std::vector<VertexData> vertData;
		glm::vec3 ka, kd, ks;
		GLfloat ns;

		//buffers
		GLuint vertexArrayObject;
		GLuint vertexBufferObject[3]; // Cada tipo de data numa posi��o (0 = posi��o, 1 = normais, 2 = coordenadas da UV)

		//Shader
		GLuint shaderProgram;
	};
}