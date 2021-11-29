#define NOMINMAX
#include "Game.hpp"

#include "Engine/Rendering.hpp"

#include <algorithm>

#include "Engine/ECS/Entity.hpp"
#include "Engine/MapLoader/MapLoader.hpp"

#include "Engine/ECS/Components/SeeingComponent.hpp"

Game::Game(GLFWwindow* window):
	m_botLoader(window),
	m_ECSManager(&ECSManager::getInstance())
{

	m_ECSManager->getGraphicsSystem()->getQuadManager()->getTexture(0).loadFromFile("resources/Textures/instanced.png");
	m_ECSManager->getGraphicsSystem()->getQuadManager()->getTexture(1).loadFromFile("resources/Textures/HealthBar.png");
	m_ECSManager->getGraphicsSystem()->getMapLoader()->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) m_ECSManager->getGraphicsSystem()->getMapLoader()->getWidth(), 
		0.5f * (float)m_ECSManager->getGraphicsSystem()->getMapLoader()->getHeight(), 
		0.1f));
	m_ECSManager->getGraphicsSystem()->getMapLoader()->getModelMatrix() = glm::scale(m_ECSManager->getGraphicsSystem()->getMapLoader()->getModelMatrix(),
		glm::vec3((float) m_ECSManager->getGraphicsSystem()->getMapLoader()->getWidth(), 
		(float)m_ECSManager->getGraphicsSystem()->getMapLoader()->getHeight(), 
		1.0f)); // Scale map to make the tile size 1x1
	m_ECSManager->getGraphicsSystem()->getCamera()->setZoom(1.0f/(0.5f * (float) std::max(m_ECSManager->getGraphicsSystem()->getMapLoader()->getWidth(), 
		m_ECSManager->getGraphicsSystem()->getMapLoader()->getHeight()))); // Zoom out so that the whole map is visible
	m_ECSManager->getGraphicsSystem()->getCamera()->setPosition(0.5f * (float)m_ECSManager->getGraphicsSystem()->getMapLoader()->getWidth(), 
		0.5f * (float)m_ECSManager->getGraphicsSystem()->getMapLoader()->getHeight());
	
	m_ECSManager->createPlayerEntity(7.f, 4.f, window);
	}	

void Game::update(float dt) {
	m_ECSManager->update(dt);
	for(BotLoader::botInstance* b : m_botLoader.m_bots) {
		Entity* e = m_ECSManager->getEntity(b->m_id);
		if (e) {
			SeeingComponent* seeingComp = static_cast<SeeingComponent*>(e->getComponent(ComponentTypeEnum::SEEING));
			b->bot->update(dt, &seeingComp->visualEntities);
		}
	}
}

void Game::reset() {
	Rendering::getInstance().reset();
	m_ECSManager->reset();

	init();
}	

Game::~Game()
{
	m_ECSManager->reset();
	//Rendering::getInstance().~Rendering();
}

void Game::init() {
	Rendering::getInstance().getCamera()->setZoom(1.0f/15.f);
	Rendering::getInstance().getCamera()->setPosition(0.5f * 15.f, 0.5f * 15.f);

	setupEntities();
}

void Game::setupEntities() {
}
