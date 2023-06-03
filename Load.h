#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>



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
}