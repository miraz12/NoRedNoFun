#pragma once
#include "Component.hpp"

class HealthComponent : public Component 
{

public:
	HealthComponent();
	
	int health;
	float invincibleTime;
	float invincibleTimer;
	int damageOnImpact;
};