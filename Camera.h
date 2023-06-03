#pragma once

#include <glm\glm.hpp>

namespace cam
{
	class Camera
	{
	public:
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec3 position;
		glm::vec3 target;
		Camera* GetInstance();
		Camera();
	private:
		static Camera* instance;
	};
}