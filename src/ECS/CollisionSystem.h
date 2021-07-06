#pragma once
#include "../ECS/System.h"

class CollisionSystem : public System
{
public:

	CollisionSystem();

	void update(float dt);

};

