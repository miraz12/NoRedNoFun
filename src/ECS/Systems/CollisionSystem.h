#pragma once
#include "System.h"

class ECSManager;
class CollisionSystem : public System
{
public:

	CollisionSystem(ECSManager *ECSManager);

	void update(float dt);

};

