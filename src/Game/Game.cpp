#define NOMINMAX
#include "Game.hpp"

#include <algorithm>

#include "../Engine/MapLoader/MapLoader.hpp"

void botMove(unsigned int key)
{
	// TODO: get entity with current id not magic 1.
	// TODO: move entity with movecomponent not through inputcomponent
	Entity &e = ECSManager::getEntity(1);
	static_cast<InputComponent*>(e.getComponent(ComponentTypeEnum::INPUT))->updateInput(key);
}

Game::Game(Rendering& rendering, GLFWwindow* window):
	m_rendering(rendering),
	m_botLoader("myBot"),
	m_botInterface(m_botLoader.newInterface()),
	m_ECSManager(&ECSManager::getInstance())
{
	MapLoader::mapInstance->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight(), 0.1f));
	MapLoader::mapInstance->getModelMatrix() = glm::scale(MapLoader::mapInstance->getModelMatrix(),
		glm::vec3((float) MapLoader::mapInstance->getWidth(), (float)MapLoader::mapInstance->getHeight(), 1.0f)); // Scale map to make the tile size 1x1
	m_rendering.getCamera()->setZoom(1.0f/(0.5f * (float) std::max(MapLoader::mapInstance->getWidth(), MapLoader::mapInstance->getHeight()))); // Zoom out so that the whole map is visible
	m_rendering.getCamera()->setPosition(0.5f * (float)MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight());
	m_botInterface->print();
	m_botInterface->output(botMove);

	Entity *botEntity = &m_ECSManager->createEntity();
	// Add componments to player
	botEntity->addComponent(new PositionComponent(m_rendering.getNewQuad()));
	botEntity->addComponent(new MovementComponent());
	botEntity->addComponent(new CollisionComponent());
	botEntity->addComponent(new InputComponent(window));
	botEntity->addComponent(new HealthComponent());

	// Test player 2 to make sure multiple quads work
	Entity& playerEntity2 = m_ECSManager->createEntity();
	// Add components to player 2
	playerEntity2.addComponent(new PositionComponent(m_rendering.getNewQuad()));
	static_cast<PositionComponent *>(playerEntity2.getComponent(ComponentTypeEnum::POSITION))->position.x = 4.0f;
	playerEntity2.addComponent(new MovementComponent());
	playerEntity2.addComponent(new InputComponent(window));
	playerEntity2.addComponent(new CollisionComponent());
	playerEntity2.addComponent(new HealthComponent());
}	

Game::~Game() {
	delete m_botInterface;
}


void Game::update(float dt) {
	m_ECSManager->update(dt);
	m_botInterface->update();
}
