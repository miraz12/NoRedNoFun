#include "MovementSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"

MovementSystem::MovementSystem(ECSManager * ECSManager) 
	: System(ECSManager, ComponentTypeEnum::POSITION, ComponentTypeEnum::MOVEMENT){

}

void MovementSystem::update(float dt)
{
	for (auto& e : m_entities) {
		PositionComponent *p = static_cast<PositionComponent *>(e->getComponent(ComponentTypeEnum::POSITION));
		MovementComponent *m = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));

		glm::vec3 normalizedAccelerationDirection(0.0f);
		bool accelerating = false;


		if (glm::length2(m->accelerationDirection) > 0.0001f) {
			normalizedAccelerationDirection = glm::normalize(m->accelerationDirection);
			accelerating = true;
		}

		if (glm::length2(m->accelerationDirection) > 1.0f) {
			m->accelerationDirection = normalizedAccelerationDirection;
		}

		glm::vec3 oldVelocity = m->velocity;
		m->velocity += m->accelerationDirection * (m->acceleration * dt);

		// Apply drag
		if (glm::length2(m->velocity) > 0.0001f) {
			glm::vec3 normalizedVel = glm::normalize(m->velocity);
			m->velocity -= normalizedVel * (1.0f - glm::dot(normalizedVel, normalizedAccelerationDirection)) * m->drag * dt;
		}

		// Limit velocity to max speed
		if (glm::length(m->velocity) > m->maxSpeed) {
			m->velocity = glm::normalize(m->velocity) * m->maxSpeed;
		}

		// Stop movement if velocity is small enough
		if (!accelerating && glm::length2(m->velocity) < 0.01f) {
			m->velocity = { 0.0f, 0.0f, 0.0f };
		}

		p->position += (oldVelocity + m->velocity) * 0.5f * dt; // This works for any update rate

		m->accelerationDirection = { 0.0f, 0.0f, 0.0f };
	}
}
