#pragma once
#include "System.hpp"
#include "../Components/InputComponent.hpp"
#include "../Components/MovementComponent.hpp"


class InputSystem: public System
{
public:

	InputSystem(ECSManager *ECSManager);

	void update(float dt);

};

