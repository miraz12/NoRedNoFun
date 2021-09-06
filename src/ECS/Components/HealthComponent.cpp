#include "HealthComponent.h"


HealthComponent::HealthComponent() : 
	health(100),
	invisTime(0.2f),
	invisTimer(0.0f) {
	m_componentType = ComponentTypeEnum::HEALTH;
}