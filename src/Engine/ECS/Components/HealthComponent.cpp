#include "HealthComponent.hpp"

#include "Rendering.hpp"

HealthComponent::HealthComponent() : 
	maxHealth(100),
	health(100),
	invincibleTime(0.2f),
	invincibleTimer(0.0f),
	damageOnImpact(0),
	healthVisualizerQuad(nullptr) {
	m_componentType = ComponentTypeEnum::HEALTH;
}

HealthComponent::HealthComponent(int health) :
	HealthComponent() {
	maxHealth = health;
	health = health;

}

HealthComponent::~HealthComponent() {
	if (healthVisualizerQuad) {
		Rendering::getInstance().getQuadManager()->returnQuad(healthVisualizerQuad);
	}
}
