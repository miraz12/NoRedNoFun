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


	Entity& playerEntity = m_ECSManager.createEntity();
	// Add componments to player
	playerEntity.addComponent(new PositionComponent(m_rendering.getNewQuad()));
	playerEntity.addComponent(new MovementComponent());
	playerEntity.addComponent(new InputComponent(window));
	playerEntity.addComponent(new CollisionComponent());

	// Test player 2 to make sure multiple quads work
	Entity& playerEntity2 = m_ECSManager.createEntity();
	// Add components to player 2
	playerEntity2.addComponent(new PositionComponent(m_rendering.getNewQuad()));
	static_cast<PositionComponent *>(playerEntity2.getComponent(ComponentTypeEnum::POSITION))->position.x = 4.0f;
	playerEntity2.addComponent(new MovementComponent());
	playerEntity2.addComponent(new InputComponent(window));
	playerEntity2.addComponent(new CollisionComponent());
}	

Game::~Game() {
	delete m_botInterface;
}

void Game::update(float dt) {
	m_ECSManager.update(dt);
}
