#pragma once
#include "Entity.h"
#include "Systems/MovementSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/CollisionSystem.h"
#include <map>
#include <string>
#include <memory>



class ECSManager
{
public:
	ECSManager();

	~ECSManager();

	//Runs through all systems
	void update(float dt);

	//adds entity and inserts it into to all matching systems
	void addEntity(Entity entity);

	void addComponent(Entity& entity, Component* component);

	//Removes an entity from all systems
	void removeEntity(int entityID);

	//Removes  componenet from entity and then the entity from all concerned systems
	void removeComponent(Entity& entity, ComponentTypeEnum component);

	const Entity& getEntity(int entityID);

private:
	//Entities
	std::vector<Entity> m_entities;

	//Systems
	std::map<std::string, std::shared_ptr<System>> m_systems;

	//Events
	std::vector<Entity> m_addEntities;
	struct addComponent_t {
		Entity& ent;
		Component* cmp;
	};
	std::vector<addComponent_t> m_addComponents;
	std::vector<int> m_removeEntities;
	struct removeComponent_t {
		Entity& ent;
		ComponentTypeEnum cmp;
	};
	std::vector<removeComponent_t> m_removeComponents;

	void addEntites();
	void addComponents();
	void removeEntities();
	void removeComponents();
};

