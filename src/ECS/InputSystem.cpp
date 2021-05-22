#include "InputSystem.h"

InputSystem::InputSystem(){
	m_requiredComponents.push_back(ComponentTypeEnum::INPUT);
}

bool System::addEntity(Entity* entity) {

	//assumes entities only has one type of component
	bool entityAdded = false;
	for (int i = 0; i < m_requiredComponents.size(); ++i) {

		if (!entity->hasComponent(m_requiredComponents[i])) {
			return entityAdded; //Component does not exist!
		}
	}

	//the right components exists in entity
	m_entities.push_back(entity);
	entityAdded = true;

	return entityAdded;
}

void System::removeEntity(int ID)
{
}

void InputSystem::update(){
	//Handle input

	for (auto &e: m_entities) {
		//Get component
		//Component& component = e->getComponent(ComponentTypeEnum::INPUT);

		//cast component

		//call on component-specific stuff
	}

}
