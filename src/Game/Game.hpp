#pragma once

#include "../Engine/Objects/Quad.hpp"
#include "../Engine/Bots/BotLoader.hpp"
#include "../Engine/ECS/ECSManager.hpp"

class Game {
public:
	Game(GLFWwindow* window);
	~Game() = default;
	
	void update(float dt);
private:
	BotLoader m_botLoader;
	ECSManager* m_ECSManager;

};

