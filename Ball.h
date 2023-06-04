#pragma once

#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS
#define GLFW_USE_DWM_SWAP_INTERVAL
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <iostream>
#include <vector>

namespace ball {

	class Ball {

	public:
		glm::vec3 currentPosition;
		float radius;
	private:
		bool hit;

		Ball(glm::vec3 position, float radius, bool hit = false) : currentPosition(position), radius(radius), hit(hit) {};
	};

	bool DetectCollision(Ball otherBall) {

		//float distance = glm::distance(this.current)
	}
}