#pragma once

#include <GLFW/glfw3.h>

#include "../Engine/Rendering.hpp"
#include "../Engine/Objects/Quad.hpp"
#include "Bots/BotLoader.h"
#include "../ECS/ECSManager.h"



class Game {
public:
	Game(Rendering &rendering, GLFWwindow* window);
	~Game();
	
	void update(float dt);
private:
	Rendering& m_rendering;
	BotLoader m_botLoader;
	BotInterface* m_botInterface;
	ECSManager* m_ECSManager;

};

