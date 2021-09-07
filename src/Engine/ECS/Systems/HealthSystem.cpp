#include "HealthSystem.hpp"
#include "../ECSManager.hpp"

#include "../Components/CollisionComponent.hpp"

HealthSystem::HealthSystem(ECSManager* ECSManager) : System(ECSManager, ComponentTypeEnum::HEALTH) {
}

void HealthSystem::update(float dt) {

    //Do all health related stuff such as damage and heal
    for (auto& e : m_entities) {
        HealthComponent* healthComp = static_cast<HealthComponent*>(e->getComponent(ComponentTypeEnum::HEALTH));
        
        healthComp->invincibleTimer -= dt;
        
        if (healthComp->invincibleTimer <= 0.0f) {
            CollisionComponent* collisionComp = static_cast<CollisionComponent*>(e->getComponent(ComponentTypeEnum::COLLISION));
            if (collisionComp) {
                //If hit by entity with damage component, reduce health in healthcomponent
                for (auto& attackingE : collisionComp->currentCollisionEntities) {
                    if (attackingE && attackingE->hasComponent(ComponentTypeEnum::DAMAGE)) {
                        DamageComponent* damageComp = static_cast<DamageComponent*>(attackingE->getComponent(ComponentTypeEnum::DAMAGE));
                        healthComp->health -= damageComp->damage;
                        healthComp->invincibleTimer = healthComp->invincibleTime;
                    }
                }

                if (collisionComp->currentCollisionEntities.size() > 0) { // Has collided with something
                    healthComp->health -= healthComp->damageOnImpact;
                    healthComp->invincibleTimer = healthComp->invincibleTime;
                }
            }
        }

        //entity is dead if health is 0
        if (healthComp->health <= 0) {
            //std::cout << "Entity: " << e->getID() << " is dead!" << std::endl;
            m_manager->removeEntity(e->getID());
        }
    }
}