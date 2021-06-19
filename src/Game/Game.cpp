#include "Game.hpp"

#include "../Engine/MapLoader/MapLoader.hpp"

Game::Game(Rendering& rendering):
	m_rendering(rendering),
	m_player(m_rendering.getNewQuad()) {
	m_rendering.getCamera()->setZoom(1.0f/15.0f); // Zoom out so that 30x30 units is visible (2x2 from the start, -1 to 1 in both directions)
	m_rendering.getMapLoader()->getModelMatrix() = glm::scale(glm::mat4(1.0f), glm::vec3(30.0f, 30.0f, 1.0f)); // Scale map by 30 to make the tile size 1x1
}

Game::~Game() {

}

void Game::processInput(GLFWwindow* window) {
	glm::vec3 movement(0.0f);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		movement += glm::vec3(0.0f, 1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		movement += glm::vec3(0.0f, -1.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		movement += glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		movement += glm::vec3(1.0f, 0.0f, 0.0f);
	}
	m_player.setAccelerationDirection(movement);
}

void Game::update(float dt) {
	m_player.update(dt);
}