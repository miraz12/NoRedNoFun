#include "Player.hpp"

#include <glm/gtx/norm.hpp>
#include <cmath>
#include <iostream>

#include "../Engine/MapLoader/MapLoader.hpp"
#include "../Engine/Physics/Shape.hpp"
#include "../Engine/Physics/SAT.hpp"

Player::Player(Quad* playerQuad, Quad* intersectionPointDisplayQuad) :
	m_playerQuad(playerQuad),
	m_intersectionPointDisplay(intersectionPointDisplayQuad),
	m_accelerationDirection(0.0f),
	m_velocity(0.0f),
	m_acceleration(20.0f),
	m_drag(10.0f),
	m_maxSpeed(7.0f),
	m_position(2.0f, 2.0f, -0.1f),
	m_rotation(0.0f),
	m_scale(0.5f) {
		m_shape.addVertex(glm::vec2(-0.5f, -0.5f));
		m_shape.addVertex(glm::vec2(0.5f, -0.5f));
		m_shape.addVertex(glm::vec2(-0.5f, 0.5f));
		m_shape.addVertex(glm::vec2(0.5f, 0.5f));

		m_shape.addNormal(glm::vec2(1.0f, 0.0f));
		m_shape.addNormal(glm::vec2(0.0f, 1.0f));

		m_intersectionPointDisplay->getModelMatrix() = glm::translate(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, -0.2f));
}

Player::~Player() {

}

Shape &Player::getShape() {
	return m_shape;
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

	glm::mat4& matrix = m_playerQuad->getModelMatrix();

	matrix = glm::translate(glm::mat4(1.0f), m_position);
	matrix = glm::rotate(matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, m_scale);

	m_shape.setTransformMatrix(matrix);

	collideWithMap();

	m_accelerationDirection = {0.0f, 0.0f, 0.0f};	

	matrix = glm::translate(glm::mat4(1.0f), m_position);
	matrix = glm::rotate(matrix, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	matrix = glm::scale(matrix, m_scale);
}

void Player::collideWithMap() {
    // Assuming that a map tile is 1x1 and map starts at 0,0

	Shape tileShape;
	tileShape.addNormal(glm::vec2(1.0f, 0.0f));
	tileShape.addNormal(glm::vec2(0.0f, 1.0f));
	
	for (int direction = 0; direction < 2; direction++) {
		for (int a = -1; a < 2; a += 2) {
			bool buildingShape = false;
			tileShape.clearVertices();
			for (int b = -1; b < 2; b++) {
				int mapTileX;
				int mapTileY;

				if (direction == 0) {
					mapTileX = (int) floor(m_position.x) + a;
					mapTileY = (int) floor(m_position.y) + b;
				}
				else {
					mapTileX = (int) floor(m_position.x) + b;
					mapTileY = (int) floor(m_position.y) + a;
				}

				bool movementAllowed = MapLoader::mapInstance->allowMovement(mapTileX, (int)MapLoader::mapInstance->getHeight() - 1 - mapTileY);
				bool testShape = false;

				if (movementAllowed == buildingShape) {
					tileShape.addVertex(glm::vec2(mapTileX, mapTileY));
					if (direction == 0) {
						tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
					}
					else {
						tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
					}

					if (buildingShape) {
						// Shape done, test it
						testShape = true;
						buildingShape = false;
					} else {
						buildingShape = true;
					}
				}
				else if (!movementAllowed && buildingShape && b == 1) {
					tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY + 1.0f));
					if (direction == 0) {
						tileShape.addVertex(glm::vec2(mapTileX, mapTileY + 1.0f));
					}
					else {
						tileShape.addVertex(glm::vec2(mapTileX + 1.0f, mapTileY));
					}
					testShape = true;
					buildingShape = false;
				}

				if (testShape) {
					glm::vec2 tempIntersectionAxis(0.0f);
					float tempIntersectionDepth = 0.0f;
					glm::vec2 intersectionPoint(0.0f);

					if (SAT::getIntersection(m_shape, tileShape, tempIntersectionAxis, tempIntersectionDepth, intersectionPoint)) {
						if (glm::length2(tempIntersectionAxis) > 0.0001f) {
							m_position += glm::vec3(tempIntersectionAxis, 0.0f)  * tempIntersectionDepth;
							glm::vec3 normalizedIntersectionAxis = {glm::normalize(tempIntersectionAxis), 0.0f};
							m_velocity -= normalizedIntersectionAxis * glm::dot(normalizedIntersectionAxis, m_velocity);
							
							// Display intersectionPoint
							glm::mat4 &matrix = m_intersectionPointDisplay->getModelMatrix();
							matrix= glm::translate(glm::mat4(1.0f), glm::vec3(intersectionPoint, -0.3f));
							matrix = glm::scale(matrix, glm::vec3(0.3f));
						}
					}
					tileShape.clearVertices();
				}
			}
		}
	}
}
