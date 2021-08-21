#pragma once
#include <vector>
#include "Components/Component.h"

class Entity
{
public:
	int m_ID;

	Entity(int ID);

	~Entity();

	//Adds component
	//Can't have more than one type of component!
	bool addComponent(Component* component);

	//Returns component based on enum ComponentTypeEnum
	Component* getComponent(ComponentTypeEnum type);

	//Check if component exists
	bool hasComponent(ComponentTypeEnum type);

	//Removes component
	void removeComponent(ComponentTypeEnum removeComponent);

private:

	std::vector<Component*> m_components;
};

