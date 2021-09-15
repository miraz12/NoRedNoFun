#pragma once

#include "Engine/Objects/Quad.hpp"
#include "Engine/Bots/BotLoader.hpp"
#include "Engine/ECS/ECSManager.hpp"

#include <vector>
#include <thread>

class Game {
public:
	Game(GLFWwindow* window);
	~Game();
	
	void update(float dt);
private:
	BotLoader m_botLoader;
	ECSManager* m_ECSManager;

	std::vector<std::thread> botThreads;

	float m_dtRef;

};

