#pragma once
#include <vector>
#include "Components/Component.hpp"

#include <string>

class Entity
{
public:
	Entity(int ID);

	~Entity();
	Entity(const Entity&) = delete;

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

	void makePlayable() { m_playable = true; }
	bool isPlayable() { return m_playable; }

private:
	int m_ID;
	bool m_playable;
	std::string m_name;
	std::vector<Component*> m_components;
};

