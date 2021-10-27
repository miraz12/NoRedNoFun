#pragma once
#include "Component.hpp"

#include "Engine/Objects/Quad.hpp"

class HealthComponent : public Component 
{

public:
	HealthComponent();
	HealthComponent(int health);
	virtual ~HealthComponent();
	int maxHealth;
	int health;
	float invincibleTime;
	float invincibleTimer;
	int damageOnImpact;
	Quad *healthVisualizerQuad; // Manually create this if a visualizer is wanted
};
