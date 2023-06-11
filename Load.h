#pragma once
#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS
#define GLFW_USE_DWM_SWAP_INTERVAL
#include <glm\glm.hpp>
#include <GL\glew.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "Ball.h"

namespace Load {

	struct Face {
		glm::vec3 positionIndexes;
		glm::vec3 normalIndexes;
		glm::vec3 texCoordsIndexes;
	};

	class Obj
	{
	public:
		void Read(const std::string, GLuint, GLuint, GLuint, GLuint, GLuint, int);
		void ReadMaterial(const std::string);
		void ReadTexture(const std::string);
		void Draw(glm::vec3, glm::vec3, glm::mat4);
		void Send(void);
		void Draw(glm::vec3, glm::vec3);

		glm::mat4 model;
		GLuint shaderProgram;

		//Ball Object
		//ball::Ball thisBall; 

		//lights

		glm::vec3 ka, kd, ks;
		GLfloat ns;
	private:

		//Vertex data types
		std::vector < glm::vec3> positions;
		std::vector < glm::vec3> normals;
		std::vector < glm::vec2> texcoords;
		std::vector < Face> faces;

		//std::vector<VertexData> vertData;

		//buffers
		GLuint posId, normId, texId, textureBindID;
		GLuint textureID;
		int counter;
		GLuint vertexArrayObject;
		GLuint vertexBufferObject[3]; // Cada tipo de data numa posi��o (0 = posi��o, 1 = normais, 2 = coordenadas da UV)

		//Shader
	};
}