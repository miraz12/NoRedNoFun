#pragma once
#include "System.hpp"

class AnimationSystem : public System
{
public:
	AnimationSystem(ECSManager* ECSManager);

	void update(float dt);

};

