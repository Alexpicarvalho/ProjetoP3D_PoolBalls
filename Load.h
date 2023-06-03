#pragma once

#include <glm\glm.hpp>
#include <gl\GL.h>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

namespace Load {

	class Obj
	{
	public:
		void Read(const std::string);
		void ReadMaterial(const std::string);
		void ReadTexture(const std::string);
		void Send(void);
		void Draw(glm::vec3, glm::vec3);

	private:
		glm::vec3 ka, kd, ks;
		GLfloat ns;
	};
}