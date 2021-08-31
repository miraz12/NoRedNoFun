#include "DamageComponent.h"

DamageComponent::DamageComponent()
	: damage(10) {
	m_componentType = ComponentTypeEnum::DAMAGE;
}