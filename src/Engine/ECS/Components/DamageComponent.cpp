#include "DamageComponent.hpp"

DamageComponent::DamageComponent()
	: damage(10) {
	m_componentType = ComponentTypeEnum::DAMAGE;
}