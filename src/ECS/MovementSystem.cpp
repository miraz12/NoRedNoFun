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

		m->move(dt, p->getPositionX(), p->getPositionY());
	}
}


