#pragma once

#include <string>
#include <glm\glm.hpp>

namespace Load {
	class Obj
	{
	public:
		void Read(const std::string);
		void Send(void);
		void Draw(glm::vec3, glm::vec3);

	};

	void Obj::Read(const std::string obj_model_filepath)
	{

	}

	void Obj::Send(void)
	{

	}

	void Obj::Draw(glm::vec3 position, glm::vec3 orientation)
	{

	}
}