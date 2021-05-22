#pragma once
#include <vector>
#include "Entity.h"
class InputSystem
{
public:

	InputSystem();

	//Adds entity to System if it contains the right components
	bool addEntity(Entity* entity);

	//Removes entity
	void removeEntity(int ID);

private:
	std::vector<ComponentTypeEnum> m_requiredComponents;
	std::vector<Entity*> m_entities;
};

