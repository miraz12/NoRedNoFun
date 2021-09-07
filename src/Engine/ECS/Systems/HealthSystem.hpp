#pragma once
#include "System.hpp"
#include "../Components/DamageComponent.hpp"
#include "../Components/HealthComponent.hpp"

class HealthSystem : public System {
public:
    HealthSystem(ECSManager* ECSManager);
    void update(float dt);
};