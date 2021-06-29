#pragma once
#include <vector>
#include "Entity.h"
#include "Component.h"

class System {

public:

	//Created many different constructors for different amount of required components
	System(ComponentTypeEnum c1)
		: m_requiredComponents{ c1 }, m_entities() {
	}
	System(ComponentTypeEnum c1, ComponentTypeEnum c2) 
		: m_requiredComponents{ c1, c2 }, m_entities() {
	}
	System(ComponentTypeEnum c1, ComponentTypeEnum c2, ComponentTypeEnum c3)
		: m_requiredComponents{ c1, c2, c3 }, m_entities() {
	}


	//Adds entity to System if it contains the right components
	virtual bool addEntity(Entity* entity){

		//assumes entities has at most one of each type of component
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

	//Removes entity
	virtual void removeEntity(int ID);

	//this function is called when the system should do its thing
	virtual void update(float dt) = 0;

protected:
	std::vector<ComponentTypeEnum> m_requiredComponents;
	std::vector<Entity*> m_entities;
};
