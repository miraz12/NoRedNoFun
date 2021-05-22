#pragma once
#include <vector>
#include "Entity.h"
#include "Component.h"

class System {

public:

	//Adds entity to System if it contains the right components
	virtual bool addEntity(Entity* entity);

	//Removes entity
	virtual void removeEntity(int ID);

	//this function is called when the system should do its thing
	virtual void update() = 0;

protected:
	std::vector<ComponentTypeEnum> m_requiredComponents;
	std::vector<Entity*> m_entities;
};
