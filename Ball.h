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
		glm::vec3 tableLimits;    // Por motivos de performance vamos guardar uma ref aos valores do limite da mesa, visto que estes não se alteram
		float radius;
	private:
		bool hit;

		Ball(glm::vec3 position, glm::vec3 tableLimits, float radius, bool hit = false) : currentPosition(position), tableLimits(tableLimits), radius(radius), hit(hit) {};

		//Colisão Bola - Bola
		bool DetectCollision(const Ball& otherBall) {

			float distance = glm::distance(currentPosition, otherBall.currentPosition);

			if (distance < radius + otherBall.radius) //Supõe-se que as bolas tenham o mesmo raio, mas vamos fazer isto de forma redundante
			{
				hit = true;
				return true;
			}
			else return false;
		}

		//Colisão Bola - Limite Da Mesa
		bool DetectCollision() {

			// Ver se a posião da bola se encontra fora da mesa em algum eixo X ou Z
			if (currentPosition.x - radius < -tableLimits.x ||
				currentPosition.x + radius > tableLimits.x ||
				currentPosition.z - radius < -tableLimits.z ||
				currentPosition.z + radius > tableLimits.z) {

				// Collision with table edge detected
				hit = true;
				return true;
			}

			// No collision
			return false;

		}

	};
}