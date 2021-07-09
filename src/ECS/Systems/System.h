#pragma once
#include <vector>
#include "../Entity.h"
#include "../Components/Component.h"

class System {

public:

	//Created many different constructors for different amount of required components
	System(ECSManager *ECSManager, ComponentTypeEnum c1)
		: m_manager(ECSManager), m_requiredComponents{ c1 }, m_entities() {
	}
	System(ECSManager* ECSManager, ComponentTypeEnum c1, ComponentTypeEnum c2)
		: m_manager(ECSManager), m_requiredComponents{ c1, c2 }, m_entities() {
	}
	System(ECSManager* ECSManager, ComponentTypeEnum c1, ComponentTypeEnum c2, ComponentTypeEnum c3)
		: m_manager(ECSManager), m_requiredComponents{ c1, c2, c3 }, m_entities() {
	}

	//Checks if entity has correct components
	bool entityHasCorrectComponents(Entity* entity) {

		//assumes entities has at most one of each type of component
		for (int i = 0; i < m_requiredComponents.size(); ++i) {

			if (!entity->hasComponent(m_requiredComponents[i])) {
				return false; //Component does not exist!
			}
		}
		return true;
	}

	//Adds entity to System if it contains the right components
	bool addEntity(Entity* entity){

		if (entityHasCorrectComponents(entity)) {

			//the right components exists in entity
			m_entities.push_back(entity);

			return true;
		}
		return false;
	}

	//checks if entity belongs to this system
	bool containsEntity(int entityID) {
		for (auto& entity : m_entities) {
			if (entity->m_ID == entityID) {
				return true;
			}
		}
		return false;
	}

	//finds entity by id and removes it if it does not contain correct components
	void removeFaultyEntity(int ID) {
		for (int i = m_entities.size() - 1; i >= 0; i--) {
			if (m_entities[i]->m_ID == ID) {
				if (!entityHasCorrectComponents(m_entities[i])) {
					m_entities.erase(m_entities.begin() + i);
				}
			}
		}
	}

	//Removes entity
	void removeEntity(int ID) {
		for (int i = m_entities.size() - 1; i >= 0; i--) {
			if (m_entities[i]->m_ID == ID) {
				m_entities.erase(m_entities.begin() + i);
			}
		}	
	}

	//this function is called when the system should do its thing
	virtual void update(float dt) = 0;

protected:
	ECSManager *m_manager;
	std::vector<ComponentTypeEnum> m_requiredComponents;
	std::vector<Entity*> m_entities;
};
