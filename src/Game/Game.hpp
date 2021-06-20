#pragma once

#include <GLFW/glfw3.h>

#include "../Engine/Rendering.hpp"
#include "../Engine/Objects/Quad.hpp"

#include "Bots/BotLoader.h"

#include "Player.hpp"

class Game {
public:
	Game(Rendering &rendering);
	~Game();

	void processInput(GLFWwindow* window);
	void update(float dt);
private:
	Rendering& m_rendering;
	Player m_player;
	BotLoader m_botLoader;
	BotInterface* m_botInterface;
};