#pragma once
#include <vector>
#include "Components/Component.hpp"

class Entity
{
public:
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
	
	void setName(std::string name) { m_name = name; };
	std::string getName() { return m_name; };

private:
	int m_ID;
	std::string m_name{"none"};
	std::vector<Component*> m_components;
};

