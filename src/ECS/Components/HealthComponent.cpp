#include "HealthComponent.h"


HealthComponent::HealthComponent() : health(100) {
	m_componentType = ComponentTypeEnum::Health;
}

void HealthComponent::damage(unsigned int hp) { health -= hp; }
void HealthComponent::heal(unsigned int hp) { health += hp;}