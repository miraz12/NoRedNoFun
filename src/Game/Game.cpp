#include "Game.hpp"

Game::Game(Rendering& rendering):
	m_rendering(rendering) {
	m_testQuad = m_rendering.getNewQuad();
}

Game::~Game() {

}

void Game::update(float dt) {
	m_testQuad->translate(glm::vec3(0.01f * dt, 0.0f, 0.0f));
}