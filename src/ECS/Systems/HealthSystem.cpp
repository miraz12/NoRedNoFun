#include "HealthSystem.h"

HealthSystem::HealthSystem(ECSManager* ECSManager) : System(ECSManager, ComponentTypeEnum::Health, ComponentTypeEnum::Attack) {
}

void HealthSystem::update(float dt) {
    // TODO: If hit by attack take damage? 
}