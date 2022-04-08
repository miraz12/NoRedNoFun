#define NOMINMAX
#include "Game.hpp"

#include <algorithm>

#include "Engine/ECS/Entity.hpp"
#include "Engine/MapLoader/MapLoader.hpp"

#include "Engine/ECS/Components/SeeingComponent.hpp"

Game::Game(GLFWwindow* window):
	m_ECSManager(&ECSManager::getInstance())
{
	GraphicsSystem* gSys = m_ECSManager->getGraphicsSystem();
	gSys->getQuadManager()->getTexture(0).loadFromFile("resources/Textures/instanced.png");
	gSys->getQuadManager()->getTexture(1).loadFromFile("resources/Textures/HealthBar.png");
	gSys->getMapLoader()->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) gSys->getMapLoader()->getWidth(),
		0.5f * (float)gSys->getMapLoader()->getHeight(),
		0.1f));
	gSys->getMapLoader()->getModelMatrix() = glm::scale(gSys->getMapLoader()->getModelMatrix(),
		glm::vec3((float) gSys->getMapLoader()->getWidth(),
		(float)gSys->getMapLoader()->getHeight(),
		1.0f)); // Scale map to make the tile size 1x1
	gSys->getCamera()->setZoom(1.0f/(0.5f * (float) std::max(gSys->getMapLoader()->getWidth(),
		gSys->getMapLoader()->getHeight()))); // Zoom out so that the whole map is visible
	gSys->getCamera()->setPosition(0.5f * (float)gSys->getMapLoader()->getWidth(),
		0.5f * (float)gSys->getMapLoader()->getHeight());
	
	m_ECSManager->createPlayerEntity(7.f, 4.f, window);
	}	

void Game::update(float dt) {
	m_ECSManager->update(dt);
}

void Game::reset() {
	m_ECSManager->getGraphicsSystem()->reset();
	m_ECSManager->reset();
	init();
}	

Game::~Game()
{
}

void Game::init() {
	m_ECSManager->getGraphicsSystem()->getCamera()->setZoom(1.0f/15.f);
	m_ECSManager->getGraphicsSystem()->getCamera()->setPosition(0.5f * 15.f, 0.5f * 15.f);

	setupEntities();
}

void Game::setupEntities() {
}
