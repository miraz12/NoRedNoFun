#include "ECSManager.hpp"
#include "Components/PositionComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/DamageComponent.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/WeaponComponent.hpp"


std::vector<Entity*> ECSManager::m_entities;

ECSManager::ECSManager()
	:m_idCounter(1), m_systems{
		{"INPUT", std::make_shared<InputSystem>(InputSystem(this))},
		{"MOVEMENT", std::make_shared<MovementSystem>(MovementSystem(this))},
		{"COLLISION", std::make_shared<CollisionSystem>(CollisionSystem(this))},
		{"HEALTH", std::make_shared<HealthSystem>(HealthSystem(this))},
		{"GRAPHICS", std::make_shared<GraphicsSystem>(GraphicsSystem(this))},
		{"WEAPON", std::make_shared<WeaponSystem>(WeaponSystem(this))}},
		m_addEntities(), m_addComponents(), m_removeEntities(), m_removeComponents()
{
}

ECSManager::~ECSManager()
{
	//Delete all entities and systems
}

void ECSManager::update(float dt)
{
	//G� igenom alla systems och g�r update
	m_systems["INPUT"]->update(dt);
	m_systems["MOVEMENT"]->update(dt);
	m_systems["COLLISION"]->update(dt);
	m_systems["HEALTH"]->update(dt);
	m_systems["GRAPHICS"]->update(dt);
	m_systems["WEAPON"]->update(dt);

	//for all entities, remove/add components
	//remove/add entities from systems
	addEntities();
	addComponents();
	removeEntities();
	removeComponents();
}

Entity& ECSManager::createEntity()
{
	Entity* e = new Entity(m_idCounter++);
	m_addEntities.push_back(e);
	return *e;
}

void ECSManager::addEntity(Entity* entity)
{
	m_addEntities.push_back(entity);
}

void ECSManager::addComponent(Entity& entity, Component* component)
{
	m_addComponents.push_back(addComponent_t{ entity, component });
}

void ECSManager::removeEntity(int entityID)
{
	m_removeEntities.push_back(entityID);
}

void ECSManager::removeComponent(Entity& entity, ComponentTypeEnum component)
{
	m_removeComponents.push_back(removeComponent_t{ entity, component });
}

Entity* ECSManager::getEntity(int entityID)
{
	for (auto& entity : m_entities) {
		if (entity->getID() == entityID) {
			return entity;
		}
	}
	return nullptr;
}

//PRIVATE

void ECSManager::addEntities()
{
	for (auto& newEntity : m_addEntities) {
		//add to manager
		m_entities.push_back(newEntity);


		//add to systems
		for (auto& system : m_systems) {
			system.second->addEntity(m_entities.back());
		}
	}
	m_addEntities.clear();
}

void ECSManager::addComponents()
{
	for (auto& components : m_addComponents) {

		//if enitity does not already have component, proceed
		if (components.ent.addComponent(components.cmp)) {

			for (auto& system : m_systems) {
				//if entity is not already belonging to the system, try and add it
				if (!system.second->containsEntity(components.ent.getID())) {
					system.second->addEntity(&components.ent);
				}
			}
		}
	}
	m_addComponents.clear();
}

void ECSManager::removeEntities()
{
	for (auto &i : m_removeEntities) {

		//delete in systems
		for (auto& system : m_systems) {
			system.second->removeEntity(i);
		}

		//delete in manager
		for (unsigned int j = 0; j < m_entities.size(); j++) {
			if (m_entities[j]->getID() == i) {
				delete m_entities[j];
				m_entities.erase(m_entities.begin() + j);
			}
		}
	}
	m_removeEntities.clear();
}

void ECSManager::removeComponents()
{
	for (auto& components : m_removeComponents) {
		components.ent.removeComponent(components.cmp);
		for (auto& system : m_systems) {
			system.second->removeFaultyEntity(components.ent.getID());
		}
	}
	m_removeComponents.clear();
}


void ECSManager::createBotEntity(BotLoader::botInstance* bot, GLFWwindow* /*window*/) {

	Entity &botEntity = createEntity();
	bot->m_id = botEntity.getID();
	botEntity.setName(bot->m_botName);
	botEntity.makePlayable();

	// Add componments to player
	addComponent(botEntity, new PositionComponent());
	addComponent(botEntity, new MovementComponent());
	addComponent(botEntity, new CollisionComponent());
	addComponent(botEntity, new HealthComponent());
	addComponent(botEntity, new GraphicsComponent());
	addComponent(botEntity, new WeaponComponent());
}


void ECSManager::createPlayerEntity(float x, float y, GLFWwindow* window) {

	Entity& playerEntity2 = createEntity();
	// Add components to player
	addComponent(playerEntity2, new PositionComponent(x, y));
	addComponent(playerEntity2, new MovementComponent());
	addComponent(playerEntity2, new InputComponent(window));
	addComponent(playerEntity2, new CollisionComponent());
	addComponent(playerEntity2, new HealthComponent());
	addComponent(playerEntity2, new DamageComponent());
	addComponent(playerEntity2, new GraphicsComponent());
	addComponent(playerEntity2, new WeaponComponent());

}