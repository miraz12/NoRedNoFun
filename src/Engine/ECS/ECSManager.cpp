#include "ECSManager.hpp"
#include "Components/PositionComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/InputComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/HealthComponent.hpp"
#include "Components/DamageComponent.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/WeaponComponent.hpp"
#include "Components/SeeingComponent.hpp"
#include "Components/CameraFocusComponent.hpp"


std::vector<Entity*> ECSManager::m_entities;

ECSManager::ECSManager()
	:m_idCounter(1), m_addEntities(), m_addComponents(), m_removeEntities(), m_removeComponents()
{
	initializeSystems();
	m_startingPositions.push_back(glm::vec2(2, 2));
	m_startingPositions.push_back(glm::vec2(28, 2));
	m_startingPositions.push_back(glm::vec2(2, 28));
	m_startingPositions.push_back(glm::vec2(28, 28));
}

ECSManager::~ECSManager()
{
	//Delete all entities and systems
	for (auto& e : m_entities) {
		delete e;
	}
	for (auto& s : m_systems) {
		delete s.second;
	}
}

void ECSManager::initializeSystems() {
	m_systems["INPUT"] =       new InputSystem(this);
	m_systems["MOVEMENT"] =    new MovementSystem(this);
	m_systems["COLLISION"] =   new CollisionSystem(this);
	m_systems["SEEING"] = 	   new SeeingSystem(this);
	m_systems["HEALTH"] =      new HealthSystem(this);
	m_systems["GRAPHICS"] =    new GraphicsSystem(this);
	m_systems["WEAPON"] =      new WeaponSystem(this);
	m_systems["CAMERAFOCUS"] = new CameraSystem(this);
	m_systems["ANIMATION"] =   new AnimationSystem(this);
}

void ECSManager::update(float dt)
{
	//for all entities, remove/add components
    //remove/add entities from systems
	addEntities();
	addComponents();
	removeEntities();
	removeComponents();

	//update all systems
	for (auto& s : m_systems) {
		s.second->update(dt);
	}
}

void ECSManager::updateRenderingSystems(float dt) {
	m_systems["ANIMATION"]->update(dt);
}

void ECSManager::reset() {
	//Delete all entities
	for (auto& e : m_entities) {
		delete e;
	}
	m_entities.clear();
	m_idCounter = 0;

	//re-init systems
	initializeSystems();
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

const int ECSManager::createPlayerEntity(float x, float y, GLFWwindow* window) {

	Entity& playerEntity = createEntity();
	playerEntity.setName("Player");
	playerEntity.makePlayable();
	// Add components to player
	addComponent(playerEntity, new PositionComponent(x, y));
	addComponent(playerEntity, new MovementComponent());
	addComponent(playerEntity, new InputComponent(window));
	addComponent(playerEntity, new CollisionComponent());
	HealthComponent* healthComp = new HealthComponent();
	healthComp->healthVisualizerQuad = getGraphicsSystem()->getNewQuad();
	healthComp->healthVisualizerQuad->setNrOfSprites(2.0f, 1.0f);
	healthComp->healthVisualizerQuad->setCurrentSprite(0.0f, 0.0f);
	healthComp->healthVisualizerQuad->setTextureIndex(1);
	addComponent(playerEntity, healthComp);
	addComponent(playerEntity, new DamageComponent());
	GraphicsComponent* graphComp = new GraphicsComponent();
	graphComp->quad->setNrOfSprites(1.0f, 1.0f);
	graphComp->quad->setCurrentSprite(0.0f, 0.0f);
	graphComp->quad->setTextureIndex(0);
	addComponent(playerEntity, graphComp);
	addComponent(playerEntity, new WeaponComponent());
	addComponent(playerEntity, new SeeingComponent());
	return playerEntity.getID();
}
