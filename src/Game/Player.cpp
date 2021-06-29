#include "Player.hpp"

#include <glm/gtx/norm.hpp>
#include <cmath>
#include <iostream>

#include "../Engine/MapLoader/MapLoader.hpp"

Player::Player(Quad* playerQuad) :
	Entity(1),
	m_playerQuad(playerQuad),
	m_accelerationDirection(0.0f),
	m_velocity(0.0f),
	m_acceleration(20.0f),
	m_drag(10.0f),
	m_maxSpeed(7.0f),
	m_position(2.0f, 2.0f, -0.1f),
	m_rotation(0.0f),
	m_scale(1.0f),
	m_matrix(m_playerQuad->getModelMatrix()) {

}

Player::~Player() {

}

void Player::setAccelerationDirection(const glm::vec2& direction) {
	m_accelerationDirection.x = direction.x;
	m_accelerationDirection.y = direction.y;
}

void Player::update(float dt) {
	glm::vec3 normalizedAccelerationDirection(0.0f);
	bool accelerating = false;

	if (glm::length2(m_accelerationDirection) > 0.0001f) {
		normalizedAccelerationDirection = glm::normalize(m_accelerationDirection);
		accelerating = true;
		m_rotation = ::atan2f(m_accelerationDirection.x, -m_accelerationDirection.y);
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

	collideWithMap();

	m_accelerationDirection = {0.0f, 0.0f, 0.0f};

	m_matrix = glm::translate(glm::mat4(1.0f), m_position);
	m_matrix = glm::rotate(m_matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	m_matrix = glm::scale(m_matrix, m_scale);
}

void Player::collideWithMap() {
	// Assuming that a map tile is 1x1 and map starts at 0,0
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			if (x == 0 && y == 0) {
				continue; // Don't do anything for the tile the player is in
			}

			int mapTileX = floor(m_position.x) + x;
			int mapTileY = floor(m_position.y) + y;
			if (!MapLoader::mapInstance->allowMovement(mapTileX, (int)MapLoader::mapInstance->getHeight() - 1 - mapTileY)) {
				// Movement not allowed, does the player overlap?

                // X-axis
                float xOverlapLeft = ((float)mapTileX + 1.0f) - (m_position.x - 0.5f);
                if (xOverlapLeft < 0.0f) {
                    continue; // No overlap
                }
                float xOverlapRight = (m_position.x + 0.5f) - ((float)mapTileX);
                if (xOverlapRight < 0.0f) {
                    continue; // No overlap
                }
                // Y-axis
                float yOverlapTop = m_position.y + 0.5f - (float)mapTileY;
                if (yOverlapTop < 0.0f) {
                    continue; // No overlap
                }
                float yOverlapBottom = ((float)mapTileY + 1.0f) - (m_position.y - 0.5f);
                if (yOverlapBottom < 0.0f) {
                    continue; // No overlap
                }

                // If we have made it here, there is a collision
                // Move back by smallest overlap
                float minX = std::min(xOverlapLeft, xOverlapRight);
                float minY = std::min(yOverlapTop, yOverlapBottom);
                if (minX < minY) {
                    // X is smallest
                    m_position.x += minX - 2.0f * minX * (xOverlapLeft > xOverlapRight);
                } else {
                    m_position.y += minY - 2.0f * minY * (yOverlapTop < yOverlapBottom);
                }
//                 std::cout << "Collision" << std::rand();

			}
		}
	}
}
