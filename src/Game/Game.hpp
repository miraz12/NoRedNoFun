#pragma once

#include <GLFW/glfw3.h>

#include "../Engine/Rendering.hpp"
#include "../Engine/Objects/Quad.hpp"

#include "Bots/BotLoader.h"

#include "../ECS/Entity.h"
#include "../ECS/Systems/MovementSystem.h"
#include "../ECS/Systems/InputSystem.h"
#include "../ECS/Systems/CollisionSystem.h"
#include "../ECS/Components/PositionComponent.h"
#include "../ECS/Components/MovementComponent.h"
#include "../ECS/Components/InputComponent.h"
#include "../ECS/Components/CollisionComponent.h"
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
	ECSManager m_ECSManager;

};

