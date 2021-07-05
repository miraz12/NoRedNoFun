#include "Player.hpp"

#include <glm/gtx/norm.hpp>
#include <cmath>
#include <iostream>

#include "../Engine/MapLoader/MapLoader.hpp"
#include "../Engine/Physics/Shape.hpp"
#include "../Engine/Physics/SAT.hpp"

Player::Player(Quad* playerQuad) :
	Entity(1), //hardcoded ID to entity
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
    // Create player shape, TODO: Don't do this repeatedly
    Shape playerShape;
    playerShape.addNormal(glm::vec2(1.0f, 0.0f));
    playerShape.addNormal(glm::vec2(0.0f, 1.0f));
    playerShape.addVertex(glm::vec2(m_position.x - 0.5f, m_position.y - 0.5f));
    playerShape.addVertex(glm::vec2(m_position.x + 0.5f, m_position.y - 0.5f));
    playerShape.addVertex(glm::vec2(m_position.x - 0.5f, m_position.y + 0.5f));
    playerShape.addVertex(glm::vec2(m_position.x + 0.5f, m_position.y + 0.5f));

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

                Shape tileShape;
                //No need to add normals in this case since they will be the same as for player shape (both are aabb's for now)
                // TODO: Change this when implementign rotations of player shape.
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
                tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
                tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY + 1.0f));

                glm::vec2 tempIntersectionAxis(0.0f);
                float tempIntersectionDepth = 0.0f;

                if (SAT::getIntersection(playerShape, tileShape, tempIntersectionAxis, tempIntersectionDepth)) {
                    if (glm::length2(tempIntersectionAxis) > 0.0001f) {
                        m_position += glm::vec3(tempIntersectionAxis.x, tempIntersectionAxis.y, 0.0f)  * tempIntersectionDepth;
                        glm::vec3 normalizedIntersectionAxis = {glm::normalize(tempIntersectionAxis).x, glm::normalize(tempIntersectionAxis).y, 0.0f};
                        m_velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m_velocity);
                    }
                }
			}
		}
	}
}
