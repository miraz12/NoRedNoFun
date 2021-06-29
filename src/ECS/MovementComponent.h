#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <cmath>

class MovementComponent : public Component
{
public:
	glm::vec3 m_accelerationDirection;
	glm::vec3 m_velocity;
	float m_acceleration;
	float m_drag;
	float m_maxSpeed;

	MovementComponent();

};