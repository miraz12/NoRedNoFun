#pragma once
#include "System.hpp"

class MovementSystem : public System
{
public:

	MovementSystem(ECSManager *ECSManager);

	void update(float dt);

};