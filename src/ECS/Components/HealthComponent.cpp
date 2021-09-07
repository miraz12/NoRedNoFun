#include "HealthComponent.h"


HealthComponent::HealthComponent() : 
	health(100),
	invincibleTime(0.2f),
	invincibleTimer(0.0f),
	damageOnImpact(0) {
	m_componentType = ComponentTypeEnum::HEALTH;
}