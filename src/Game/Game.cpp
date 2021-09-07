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

void botMove(unsigned int key, BotInterface* bot)
{
	Entity *e = ECSManager::getEntity(bot->m_id);
	if (e) {
		static_cast<InputComponent*>(e->getComponent(ComponentTypeEnum::INPUT))->updateInput(key);
	}
}

Game::Game(GLFWwindow* window):
	m_botLoader(window),
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
	
	m_ECSManager->createPlayerEntity(7.f, 4.f, window);
	}	

void Game::update(float dt) {
	m_ECSManager->update(dt);
	for(BotLoader::botInstance* b : m_botLoader.m_bots) {
		b->bot->update(dt);
	}
}
