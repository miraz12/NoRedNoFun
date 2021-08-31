#pragma once
#include <vector>
#include "Components/Component.h"

class Entity
{
public:
	std::vector<Entity*>collisionEntities;
	//This could be in healthcomponent but it could apply to entities without
	//health, that just expire such as powerups.
	bool isAlive;
	

	Entity(int ID);

	~Entity();

	const int getID();

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
	int m_ID;
	std::vector<Component*> m_components;
};

