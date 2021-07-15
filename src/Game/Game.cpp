#include "Game.hpp"

#include <algorithm>

#include "../Engine/MapLoader/MapLoader.hpp"

Game::Game(Rendering& rendering):
	m_rendering(rendering),
	m_player(m_rendering.getNewQuad(), m_rendering.getNewQuad()),
	m_botLoader("myBot"),
	m_botInterface(m_botLoader.newInterface()) {
	MapLoader::mapInstance->getModelMatrix() = glm::translate(glm::mat4(1.0f),
		glm::vec3(0.5f * (float) MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight(), 0.1f));
	MapLoader::mapInstance->getModelMatrix() = glm::scale(MapLoader::mapInstance->getModelMatrix(),
		glm::vec3((float) MapLoader::mapInstance->getWidth(), (float)MapLoader::mapInstance->getHeight(), 1.0f)); // Scale map to make the tile size 1x1
	m_rendering.getCamera()->setZoom(1.0f/(0.5f * (float) max(MapLoader::mapInstance->getWidth(), MapLoader::mapInstance->getHeight()))); // Zoom out so that the whole map is visible
	m_rendering.getCamera()->setPosition(0.5f * (float)MapLoader::mapInstance->getWidth(), 0.5f * (float)MapLoader::mapInstance->getHeight());
	m_botInterface->print();
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
	m_player.setAccelerationDirection(movement);
}

void Game::update(float dt) {
	m_player.update(dt);
}
