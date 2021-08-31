#include "HealthSystem.h"


HealthSystem::HealthSystem(ECSManager* ECSManager) : System(ECSManager, ComponentTypeEnum::Health, ComponentTypeEnum::Attack) {
}

void HealthSystem::update(float dt) {

    //Do all health related stuff such as damage and heal
    for (auto& e : m_entities) {
        HealthComponent* health = static_cast<HealthComponent*>(e->getComponent(ComponentTypeEnum::Health));

        //If hit by entity with damage component, reduce health in healthcomponent
        for (auto& attackingE : e->collisionEntities) {

            if (attackingE->hasComponent(ComponentTypeEnum::DAMAGE)) {
                DamageComponent* damage = static_cast<DamageComponent*>(attackingE->getComponent(ComponentTypeEnum::DAMAGE));
                health->damage(damage->damage);

                //entity is dead if health is 0
                if (health->getHealth() <= 0) {
                    e->isAlive = false;
                }
            }
        }
        e->collisionEntities.clear();
    }
}