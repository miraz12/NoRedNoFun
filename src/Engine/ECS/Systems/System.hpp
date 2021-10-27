#pragma once
#include <vector>
#include "../Entity.hpp"
#include "../Components/Component.hpp"

class ECSManager;
class System {

public:

	//Created many different constructors for different amount of required components
	System(ECSManager* ECSManager, ComponentTypeEnum c1);
		
	System(ECSManager* ECSManager, ComponentTypeEnum c1, ComponentTypeEnum c2);

	System(ECSManager* ECSManager, ComponentTypeEnum c1, ComponentTypeEnum c2, ComponentTypeEnum c3);
		

	//Checks if entity has correct components
	bool entityHasCorrectComponents(Entity* entity);

	//Adds entity to System if it contains the right components
	bool addEntity(Entity* entity); 

	//checks if entity belongs to this system
	bool containsEntity(int entityID);

	//finds entity by id and removes it if it does not contain correct components
	void removeFaultyEntity(int ID);

	//Removes entity
	void removeEntity(int ID);

	//this function is called when the system should do its thing
	virtual void update(float dt) = 0;

	//Initialize system
	virtual void initialize() {};

protected:
	ECSManager *m_manager;
	std::vector<ComponentTypeEnum> m_requiredComponents;
	std::vector<Entity*> m_entities;
};
