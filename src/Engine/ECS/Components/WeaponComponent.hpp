#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>

class WeaponComponent : public Component
{
public:
    glm::vec2 aimDirection;
    glm::vec2 muzzlePosition;
    bool fire;
    float cooldown;
    float fireRate;
    float speed;

	WeaponComponent();
};

