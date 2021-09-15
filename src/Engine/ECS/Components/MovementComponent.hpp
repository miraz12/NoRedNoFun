#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <cmath>
#include <atomic>

class MovementComponent : public Component
{
public:
	struct accDir {
		std::atomic<float> x{0.0f}; 
		std::atomic<float> y{0.0f}; 
	};
	accDir accelerationDirection;
	glm::vec3 velocity;
	float acceleration;
	float drag;
	float maxSpeed;

	MovementComponent();
	MovementComponent(float velX, float velY);
};