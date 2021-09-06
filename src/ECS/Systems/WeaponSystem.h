#pragma once
#include "System.h"

class ECSManager;

class WeaponSystem : public System
{
public:

	WeaponSystem(ECSManager *ECSManager);

	void update(float dt);

};