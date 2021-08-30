#define NOMINMAX
#include "Game.hpp"

#include <algorithm>

#include "../Engine/MapLoader/MapLoader.hpp"


Game::Game(Rendering& rendering, GLFWwindow* window):
	m_rendering(rendering),
	m_botLoader("myBot"),
	m_botInterface(m_botLoader.newInterface()),
	m_ECSManager()
{
	MapLoader::mapInstance->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight(), 0.1f));
	MapLoader::mapInstance->getModelMatrix() = glm::scale(MapLoader::mapInstance->getModelMatrix(),
		glm::vec3((float) MapLoader::mapInstance->getWidth(), (float)MapLoader::mapInstance->getHeight(), 1.0f)); // Scale map to make the tile size 1x1
	m_rendering.getCamera()->setZoom(1.0f/(0.5f * (float) std::max(MapLoader::mapInstance->getWidth(), MapLoader::mapInstance->getHeight()))); // Zoom out so that the whole map is visible
	m_rendering.getCamera()->setPosition(0.5f * (float)MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight());
	m_botInterface->print();


	int playerEntity = m_ECSManager.createEntity();
	// Add componments to player
	m_ECSManager.addComponent(playerEntity, new PositionComponent(m_rendering.getNewQuad(), 2.0f, 2.0f));
	m_ECSManager.addComponent(playerEntity, new MovementComponent());
	m_ECSManager.addComponent(playerEntity, new InputComponent(window));
	m_ECSManager.addComponent(playerEntity, new CollisionComponent());
	m_ECSManager.addComponent(playerEntity, new BotComponent(m_botInterface));

	// Test player 2 to make sure multiple quads work
	int playerEntity2 = m_ECSManager.createEntity();
	// Add components to player 2
	m_ECSManager.addComponent(playerEntity2, new PositionComponent(m_rendering.getNewQuad(), 4.0f, 2.0f));
	m_ECSManager.addComponent(playerEntity2, new MovementComponent());
	m_ECSManager.addComponent(playerEntity2, new InputComponent(window));
	m_ECSManager.addComponent(playerEntity2, new CollisionComponent());
}	

Game::~Game() {
	delete m_botInterface;
}

void Game::update(float dt) {
	m_ECSManager.update(dt);
}
