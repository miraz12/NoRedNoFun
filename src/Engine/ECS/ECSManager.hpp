#pragma once
#include "Entity.hpp"
#include "Systems/MovementSystem.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/CollisionSystem.hpp"
#include "Systems/HealthSystem.hpp"
#include "Systems/GraphicsSystem.hpp"
#include "Systems/WeaponSystem.hpp"
#include "Systems/SeeingSystem.hpp"
#include "../Bots/BotLoader.hpp"

#include <map>
#include <string>
#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>

class ECSManager
{
public:
	static ECSManager& getInstance() {
		static ECSManager instance; 
		return instance;
    }

	ECSManager(ECSManager const&) = delete;
	void operator=(ECSManager const&) = delete;

	~ECSManager();

	//Runs through all systems
	void update(float dt);

	//creates and returns a new entity
	Entity& createEntity();

	//adds entity and inserts it into to all matching systems
	void addEntity(Entity* entity);

	//adds component to entity and inserts it to matching systems
	void addComponent(Entity& entity, Component* component);

	//Removes an entity from all systems
	void removeEntity(int entityID);

	//Removes  componenet from entity and then the entity from all concerned systems
	void removeComponent(Entity& entity, ComponentTypeEnum component);

	// Add and setup a new bot
	void createBotEntity(BotLoader::botInstance* bot, GLFWwindow* window);

	// Create a controllable entity at position x,y
	const int createPlayerEntity(float x, float y, GLFWwindow* window);

	//Returns entity by ID, or NULL if it does not exist
	static Entity* getEntity(int entityID);

private:

	ECSManager();
	//Entities
	int m_idCounter;
	static std::vector<Entity*> m_entities;

	//Systems
	std::map<std::string, std::shared_ptr<System>> m_systems;

	//Events
	std::vector<Entity*> m_addEntities;
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

	void addEntities();
	void addComponents();
	void removeEntities();
	void removeComponents();
};

