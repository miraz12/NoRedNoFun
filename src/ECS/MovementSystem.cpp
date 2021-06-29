#include "MovementSystem.h"
#include "PositionComponent.h"
#include "MovementComponent.h"

MovementSystem::MovementSystem() 
	: System(ComponentTypeEnum::POSITION, ComponentTypeEnum::MOVEMENT){

}

void MovementSystem::update(float dt)
{
	for (auto& e : m_entities) {
		PositionComponent *p = static_cast<PositionComponent *>(e->getComponent(ComponentTypeEnum::POSITION));
		MovementComponent *m = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));


		glm::vec3 normalizedAccelerationDirection(0.0f);
		bool accelerating = false;


		if (glm::length2(m->m_accelerationDirection) > 0.0001f) {
			normalizedAccelerationDirection = glm::normalize(m->m_accelerationDirection);
			accelerating = true;
			p->m_rotation = ::atan2f(m->m_accelerationDirection.x, -m->m_accelerationDirection.y);
		}

		if (glm::length2(m->m_accelerationDirection) > 1.0f) {
			m->m_accelerationDirection = normalizedAccelerationDirection;
		}

		glm::vec3 oldVelocity = m->m_velocity;
		m->m_velocity += m->m_accelerationDirection * (m->m_acceleration * dt);

		// Apply drag
		if (glm::length2(m->m_velocity) > 0.0001f) {
			glm::vec3 normalizedVel = glm::normalize(m->m_velocity);
			m->m_velocity -= normalizedVel * (1.0f - glm::dot(normalizedVel, normalizedAccelerationDirection)) * m->m_drag * dt;
		}

		// Limit velocity to max speed
		if (glm::length(m->m_velocity) > m->m_maxSpeed) {
			m->m_velocity = glm::normalize(m->m_velocity) * m->m_maxSpeed;
		}

		// Stop player if velocity is small enough
		if (!accelerating && glm::length2(m->m_velocity) < 0.01f) {
			m->m_velocity = { 0.0f, 0.0f, 0.0f };
		}

		p->m_position += (oldVelocity + m->m_velocity) * 0.5f * dt; // This works for any update rate

		//collideWithMap();

		m->m_accelerationDirection = { 0.0f, 0.0f, 0.0f };

		p->m_matrix = glm::translate(glm::mat4(1.0f), p->m_position);
		p->m_matrix = glm::rotate(p->m_matrix, p->m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
		p->m_matrix = glm::scale(p->m_matrix, p->m_scale);

		//m->move(dt, p->getPositionX(), p->getPositionY());
	}
}


