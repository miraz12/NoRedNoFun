#pragma once

#include "Component.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <cmath>

class MovementComponent : public Component
{
public:
	glm::vec3 accelerationDirection;
	glm::vec3 velocity;
	float acceleration;
	float drag;
	float maxSpeed;

	MovementComponent();
	MovementComponent(float velX, float velY);
};