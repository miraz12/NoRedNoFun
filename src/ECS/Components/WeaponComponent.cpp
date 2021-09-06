#include "WeaponComponent.h"

WeaponComponent::WeaponComponent() :
    aimDirection(0.0f, 1.0f),
    muzzlePosition(0.0f, 0.0f),
    fire(false),
    cooldown(0.0f),
    fireRate(1.0f),
    speed(5.0f) {

    m_componentType = ComponentTypeEnum::WEAPON;
}