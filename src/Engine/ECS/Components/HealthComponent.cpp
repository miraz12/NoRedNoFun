#include "HealthComponent.hpp"

#include "ECS/ECSManager.hpp"

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
		ECSManager::getInstance().getGraphicsSystem()->getQuadManager()->returnQuad(healthVisualizerQuad);
	}
}
