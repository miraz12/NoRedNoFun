#pragma once
#include "System.hpp"

class ECSManager;

class WeaponSystem : public System
{
public:

	WeaponSystem(ECSManager *ECSManager);

	void update(float dt);

};