#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Engine/Objects/Quad.hpp"
#include "../Engine/Physics/Shape.hpp"

class Player {
public:
	Player(Quad& playerQuad, Quad& intersectionPointDisplayQuad);
	virtual ~Player();

	Shape &getShape();

	void setAccelerationDirection(const glm::vec2 &direction);
	void update(float dt);
private:
	void collideWithMap();

	Quad& m_playerQuad;
	Quad& m_intersectionPointDisplay;
	Shape m_shape;

	// Movement
	glm::vec3 m_accelerationDirection;
	glm::vec3 m_velocity;
	float m_acceleration;
	float m_drag;
	float m_maxSpeed;

	// Visual properties
	glm::vec3 m_position;
	float m_rotation;
	glm::vec3 m_scale;
	glm::mat4& m_matrix;
};
