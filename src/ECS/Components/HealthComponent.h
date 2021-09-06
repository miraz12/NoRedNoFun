#pragma once
#include "Component.h"

class HealthComponent : public Component 
{

public:
	HealthComponent();
	
	int health;
	float invisTime;
	float invisTimer;
};