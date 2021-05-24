#include "InputSystem.h"

InputSystem::InputSystem() 
	: System(ComponentTypeEnum::INPUT){
}

bool System::addEntity(Entity* entity) {

	//assumes entities only has one type of component
	bool entityAdded = false;
	for (int i = 0; i < m_requiredComponents.size(); ++i) {

		if (!entity->hasComponent(m_requiredComponents[i])) {
			return false; //Component does not exist!
		}
	}

	//the right components exists in entity
	m_entities.push_back(entity);

	return true;
}

void System::removeEntity(int ID)
{
}

void InputSystem::update(){
	//Handle input


	for (auto &e: m_entities) {
		//Get component(s)
		InputComponent *input = static_cast<InputComponent *>(e->getComponent(ComponentTypeEnum::INPUT));

		//call on component-specific stuff
	}

}
