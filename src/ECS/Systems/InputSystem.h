#pragma once
#include "System.h"
#include "../Components/InputComponent.h"
#include "../Components/MovementComponent.h"

class ECSManager;
class InputSystem: public System
{
public:

	InputSystem(ECSManager *ECSManager);

	void update(float dt);


private:

};

