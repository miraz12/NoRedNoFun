#include "MovementComponent.h"
#include "../Engine/MapLoader/MapLoader.hpp"

MovementComponent::MovementComponent() :
	m_accelerationDirection(0.0f),
	m_velocity(0.0f),
	m_acceleration(20.0f),
	m_drag(10.0f),
	m_maxSpeed(7.0f){

}

//void MovementComponent::move(float dt, float &x, float &y) {
//	m_velocity = m_velocity * dt;
//
//	float newPosX = x + m_velocity.x;
//	float newPosY = y + m_velocity.y;
//	if(MapLoader::mapInstance->allowMovement(newPosX, newPosY)) {
//		x = newPosX;
//		y = newPosY;
//	}
//}

//void MovementComponent::setVelocity(glm::vec2 v) {
//	m_velocity = v;
//}