#pragma once
#include "System.hpp"

class CollisionSystem : public System
{
public:

	CollisionSystem(ECSManager *ECSManager);

	void update(float dt);

private:
	void collideWithMap(Entity* e);
};

