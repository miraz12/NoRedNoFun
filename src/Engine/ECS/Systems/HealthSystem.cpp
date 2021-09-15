#include "HealthSystem.hpp"
#include "ECS/ECSManager.hpp"

#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"

#include <algorithm>

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
            if(e->isPlayable()) {
                std::cout << "Entity: " << e->getName() << " is dead!" << std::endl;
            }
            m_manager->removeEntity(e->getID());
        }
        else {
            healthComp->health = std::min(healthComp->health, healthComp->maxHealth);

            PositionComponent *p = static_cast<PositionComponent *>(e->getComponent(ComponentTypeEnum::POSITION));
            if (healthComp->healthVisualizerQuad && p) {
                healthComp->healthVisualizerQuad->setCurrentSprite(
                    (float)(healthComp->maxHealth - healthComp->health) / (float)std::max(healthComp->maxHealth, 1),
                    healthComp->healthVisualizerQuad->getCurrentSprite().y);
                
                glm::mat4 &modelMatrix = healthComp->healthVisualizerQuad->getModelMatrix();
                modelMatrix = glm::translate(glm::mat4(1.0f), p->position + glm::vec3(0.0f, 0.5f, -0.3f));
                modelMatrix = glm::scale(modelMatrix, glm::vec3(1.0f, 0.4f, 1.0f));
            }
        } 
    }
}