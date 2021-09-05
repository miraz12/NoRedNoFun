#include "HealthComponent.h"


HealthComponent::HealthComponent() : health(100) {
	m_componentType = ComponentTypeEnum::HEALTH;
}