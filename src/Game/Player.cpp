#include "Player.hpp"

#include <cmath>
#include <glm/gtx/norm.hpp>

Player::Player(Quad* playerQuad) :
	m_playerQuad(playerQuad),
	m_accelerationDirection(0.0f),
	m_velocity(0.0f),
	m_acceleration(20.0f),
	m_drag(10.0f),
	m_maxSpeed(5.0f),
	m_position(4.0f, 0.0f, -0.1f),
	m_rotation(0.0f),
	m_scale(1.0f),
	m_matrix(m_playerQuad->getModelMatrix()) {

}

Player::~Player() {

}

void Player::setAccelerationDirection(const glm::vec2& direction) {
	m_accelerationDirection.x = direction.x;
	m_accelerationDirection.y = direction.y;
	m_rotation = std::atan2f(direction.x, -direction.y);
}

void Player::update(float dt) {
	glm::vec3 normalizedAccelerationDirection(0.0f);
	bool accelerating = false;

	if (glm::length2(m_accelerationDirection) > 0.0001f) {
		normalizedAccelerationDirection = glm::normalize(m_accelerationDirection);
		accelerating = true;
	}

	if (glm::length2(m_accelerationDirection) > 1.0f) {
		m_accelerationDirection = normalizedAccelerationDirection;
	}

	glm::vec3 oldVelocity = m_velocity;
	m_velocity += m_accelerationDirection * (m_acceleration * dt); 

	// Apply drag
	if (glm::length2(m_velocity) > 0.0001f) {
		glm::vec3 normalizedVel = glm::normalize(m_velocity);
		m_velocity -= normalizedVel * (1.0f - glm::dot(normalizedVel, normalizedAccelerationDirection)) * m_drag * dt;
	}

	// Limit velocity to max speed
	if (glm::length(m_velocity) > m_maxSpeed) {
		m_velocity = glm::normalize(m_velocity) * m_maxSpeed;
	}

	// Stop player if velocity is small enough
	if (!accelerating && glm::length2(m_velocity) < 0.01f) {
		m_velocity = { 0.0f, 0.0f, 0.0f };
	}

	m_position += (oldVelocity + m_velocity) * 0.5f * dt; // This works for any update rate

	m_accelerationDirection = {0.0f, 0.0f, 0.0f};

	m_matrix = glm::mat4(1.0f);
	m_matrix = glm::translate(m_matrix, m_position);
	m_matrix = glm::rotate(m_matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_matrix = glm::scale(m_matrix, m_scale);
}
