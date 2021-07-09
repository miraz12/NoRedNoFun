#define NOMINMAX
#include "Game.hpp"

#include "../Engine/MapLoader/MapLoader.hpp"


Game::Game(Rendering& rendering, GLFWwindow* window):
	m_rendering(rendering),
	/*m_player(m_rendering.getNewQuad()),*/
	m_botLoader("myBot"),
	m_botInterface(m_botLoader.newInterface()),
{
	MapLoader::mapInstance->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight(), 0.1f));
	MapLoader::mapInstance->getModelMatrix() = glm::scale(MapLoader::mapInstance->getModelMatrix(),
		glm::vec3((float) MapLoader::mapInstance->getWidth(), (float)MapLoader::mapInstance->getHeight(), 1.0f)); // Scale map to make the tile size 1x1
	m_rendering.getCamera()->setZoom(1.0f/(0.5f * (float) std::max(MapLoader::mapInstance->getWidth(), MapLoader::mapInstance->getHeight()))); // Zoom out so that the whole map is visible
	m_rendering.getCamera()->setPosition(0.5f * (float)MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight());
	m_botInterface->print();

	//Lägg till komponenter till player
	m_player.addComponent(new PositionComponent(m_rendering.getNewQuad()->getModelMatrix()));
	m_player.addComponent(new MovementComponent());
	m_player.addComponent(new InputComponent(window));
	m_player.addComponent(new CollisionComponent());

	//Lägg till player i system
	m_inputSystem.addEntity(&m_player);
	m_movementSystem.addEntity(&m_player);
	m_collisionSystem.addEntity(&m_player);
}	

Game::~Game() {
	delete m_botInterface;
}

void Game::processInput(GLFWwindow* window) {
	glm::vec3 movement(0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		movement.y += 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		movement.y += -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		movement.x += -1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		movement.x += 1.0f;
	}
	//m_player.setAccelerationDirection(movement);
}

void Game::update(float dt) {
	//m_player.update(dt);
}
