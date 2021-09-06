#define NOMINMAX
#include "Game.hpp"

#include "../Engine/Rendering.hpp"

#include <algorithm>

#include "../ECS/Entity.h"

#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/MovementComponent.h"
#include "../ECS/Components/InputComponent.h"
#include "../ECS/Components/CollisionComponent.h"
#include "../ECS/Components/HealthComponent.h"
#include "../ECS/Components/DamageComponent.h"
#include "../ECS/Components/GraphicsComponent.h"
#include "../ECS/Components/WeaponComponent.h"

#include "../Engine/MapLoader/MapLoader.hpp"

void botMove(unsigned int key)
{
	// TODO: get entity with current id not magic 1.
	// TODO: move entity with movecomponent not through inputcomponent
	Entity *e = ECSManager::getEntity(1);
	if (e) {
		static_cast<InputComponent*>(e->getComponent(ComponentTypeEnum::INPUT))->updateInput(key);
	}
}

Game::Game(GLFWwindow* window):
	m_botLoader("myBot"),
	m_botInterface(m_botLoader.newInterface()),
	m_ECSManager(&ECSManager::getInstance())
{
	Rendering::getInstance().getMapLoader()->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) Rendering::getInstance().getMapLoader()->getWidth(), 
		0.5f * (float)Rendering::getInstance().getMapLoader()->getHeight(), 
		0.1f));
	Rendering::getInstance().getMapLoader()->getModelMatrix() = glm::scale(Rendering::getInstance().getMapLoader()->getModelMatrix(),
		glm::vec3((float) Rendering::getInstance().getMapLoader()->getWidth(), 
		(float)Rendering::getInstance().getMapLoader()->getHeight(), 
		1.0f)); // Scale map to make the tile size 1x1
	Rendering::getInstance().getCamera()->setZoom(1.0f/(0.5f * (float) std::max(Rendering::getInstance().getMapLoader()->getWidth(), 
		Rendering::getInstance().getMapLoader()->getHeight()))); // Zoom out so that the whole map is visible
	Rendering::getInstance().getCamera()->setPosition(0.5f * (float)Rendering::getInstance().getMapLoader()->getWidth(), 
		0.5f * (float)Rendering::getInstance().getMapLoader()->getHeight());
	m_botInterface->print();
	m_botInterface->output(botMove);

	Entity &botEntity = m_ECSManager->createEntity();
	// Add componments to player
	m_ECSManager->addComponent(botEntity, new PositionComponent());
	m_ECSManager->addComponent(botEntity, new MovementComponent());
	m_ECSManager->addComponent(botEntity, new CollisionComponent());
	m_ECSManager->addComponent(botEntity, new InputComponent(window));
	m_ECSManager->addComponent(botEntity, new HealthComponent());
	m_ECSManager->addComponent(botEntity, new GraphicsComponent());

	// Test player 2 to make sure multiple quads work
	Entity& playerEntity2 = m_ECSManager->createEntity();
	// Add components to player 2
	m_ECSManager->addComponent(playerEntity2, new PositionComponent(7.0f, 4.0f));
	m_ECSManager->addComponent(playerEntity2, new MovementComponent());
	m_ECSManager->addComponent(playerEntity2, new InputComponent(window));
	m_ECSManager->addComponent(playerEntity2, new CollisionComponent());
	m_ECSManager->addComponent(playerEntity2, new HealthComponent());
	m_ECSManager->addComponent(playerEntity2, new DamageComponent());
	m_ECSManager->addComponent(playerEntity2, new GraphicsComponent());
	m_ECSManager->addComponent(playerEntity2, new WeaponComponent());
}	

Game::~Game() {
	delete m_botInterface;
}


void Game::update(float dt) {
	m_ECSManager->update(dt);
	m_botInterface->update();
}
