#include "MovementComponent.h"

MovementComponent::MovementComponent() :
	m_velocity(0.0f) {

}

void MovementComponent::move(float dt, float &x, float &y) {
	m_velocity = m_velocity * dt;

	x = x + m_velocity.x;
	y = y + m_velocity.y;
}

void MovementComponent::setVelocity(glm::vec2 v) {
	m_velocity = v;
}