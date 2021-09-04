#pragma once
#include "Component.h"

class HealthComponent : public Component 
{

public:
	HealthComponent();
	
	int health;
private:
};