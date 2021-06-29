#pragma once

#include <GLFW/glfw3.h>

#include "../Engine/Rendering.hpp"
#include "../Engine/Objects/Quad.hpp"

#include "Bots/BotLoader.h"

#include "Player.hpp"
#include "../ECS/Entity.h"
#include "../ECS/MovementSystem.h"
#include "../ECS/InputSystem.h"
#include "../ECS/PositionComponent.h"
#include "../ECS/MovementComponent.h"
#include "../ECS/InputComponent.h"

class Game {
public:
	Game(Rendering &rendering, GLFWwindow* window);
	~Game();

	void processInput(GLFWwindow* window);
	void update(float dt);
private:
	Rendering& m_rendering;
	Player m_player;
	BotLoader m_botLoader;
	BotInterface* m_botInterface;

	//Systems
	MovementSystem m_movementSystem; 
	InputSystem m_inputSystem;
};