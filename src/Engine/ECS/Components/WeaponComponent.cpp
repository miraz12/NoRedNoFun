#include "WeaponComponent.hpp"

WeaponComponent::WeaponComponent() :
    aimDirection(0.0f, 1.0f),
    muzzlePosition(0.0f, 0.0f),
    fire(false),
    cooldown(0.0f),
    fireRate(0.1f),
    speed(10.0f) {

    m_componentType = ComponentTypeEnum::WEAPON;
}