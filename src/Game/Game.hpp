#pragma once

#include "Engine/Objects/Quad.hpp"
#include "Engine/Bots/BotLoader.hpp"
#include "Engine/ECS/ECSManager.hpp"

class Game {
public:
	Game(GLFWwindow* window);
	~Game();
	
	void update(float dt);
	void reset();
private:
	void init();
	void setupEntities();

	GLFWwindow* m_window;
	ECSManager* m_ECSManager;
	BotLoader m_botLoader;

};

