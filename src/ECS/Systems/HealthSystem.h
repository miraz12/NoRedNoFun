#pragma once
#include "System.h"
#include "../Components/DamageComponent.h"
#include "../Components/HealthComponent.h"

class HealthSystem : public System {
public:
    HealthSystem(ECSManager* ECSManager);
    void update(float dt);
};