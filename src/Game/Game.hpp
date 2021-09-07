#pragma once

#include "../Engine/Objects/Quad.hpp"
#include "Bots/BotLoader.h"
#include "../ECS/ECSManager.h"

class Game {
public:
	Game(GLFWwindow* window);
	~Game() = default;
	
	void update(float dt);
private:
	BotLoader m_botLoader;
	ECSManager* m_ECSManager;

};

