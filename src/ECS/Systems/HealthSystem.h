#pragma once
#include "System.h"

class HealthSystem : public System {
public:
    HealthSystem(ECSManager* ECSManager);
    void update(float dt);
};