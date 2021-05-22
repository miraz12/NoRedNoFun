#pragma once
#include <vector>
#include "Component.h"

class Entity
{
public:
	int ID;

	Entity();

	//Adds component
	void addComponent(Component *component);

	//Returns component based on enum ComponentTypeEnum
	Component& getComponent(ComponentTypeEnum type);

	//Check if component exists
	bool hasComponent(ComponentTypeEnum type);

private:

	std::vector<Component*> m_components;
};

