#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "../Engine/Objects/Quad.hpp"
#include "../ECS/Entity.h"

class Player : public Entity { //inheriting from entity(instead of being an entity) for now just to try out ECS
public:
	Player(Quad* playerQuad);
	virtual ~Player();

	void setAccelerationDirection(const glm::vec2 &direction);
	void update(float dt);
private:
	void collideWithMap();

	Quad* m_playerQuad;

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
