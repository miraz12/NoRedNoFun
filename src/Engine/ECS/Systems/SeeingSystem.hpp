#pragma once
#include "System.hpp"

class SeeingSystem : public System {
public:
	SeeingSystem(ECSManager *ECSManager);

	void update(float dt);
};

