#include "WeaponSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/WeaponComponent.hpp"
#include "ECS/Components/GraphicsComponent.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/DamageComponent.hpp"

#include "ECS/ECSManager.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

WeaponSystem::WeaponSystem(ECSManager * ECSManager) 
	: System(ECSManager, ComponentTypeEnum::POSITION, ComponentTypeEnum::WEAPON){

}

void WeaponSystem::update(float dt)
{
	for (auto& e : m_entities) {
		WeaponComponent* weapon = static_cast<WeaponComponent*>(e->getComponent(ComponentTypeEnum::WEAPON));
        weapon->cooldown -= dt;

        if (weapon->fire && weapon->cooldown <= 0.0f) {
            PositionComponent* entityPos = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
            MovementComponent* entityMov = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));
            weapon->muzzlePosition = entityPos->calculateMatrix() * glm::vec4(0.0, -0.8f, -0.1f, 1.0f);
            weapon->aimDirection = glm::rotate(glm::vec2(0.0f, -1.0f), entityPos->rotation);

            Entity &projectileEntity = m_manager->createEntity();
			// Add componments to projectile
            PositionComponent* projPos = new PositionComponent(weapon->muzzlePosition.x, weapon->muzzlePosition.y);
            projPos->scale = glm::vec3(0.3f, 0.3f, 1.0f);
			m_manager->addComponent(projectileEntity, projPos);
			MovementComponent* projMove = new MovementComponent();
            projMove->maxSpeed = 40.0f;
            projMove->velocity = {weapon->aimDirection.x * weapon->speed, weapon->aimDirection.y * weapon->speed, 0.0f};
            if (entityMov) { // Add entity (holding weapon) velocity to projectile velocity
                projMove->velocity += entityMov->velocity;
            }
			projMove->drag = 0.0f;
			m_manager->addComponent(projectileEntity, projMove);
            CollisionComponent* projCollision = new CollisionComponent();
            projCollision->effectMovement = false;
			m_manager->addComponent(projectileEntity, projCollision);
            GraphicsComponent* graphComp = new GraphicsComponent();
            graphComp->quad->setNrOfSprites(1.0f, 1.5f);
            graphComp->quad->setCurrentSprite(0.0f, 0.0f);
			m_manager->addComponent(projectileEntity, graphComp);
            m_manager->addComponent(projectileEntity, new DamageComponent());
            HealthComponent* projHealth = new HealthComponent();
            projHealth->health = 1;
            projHealth->damageOnImpact = 1; 
            m_manager->addComponent(projectileEntity, projHealth);

            weapon->cooldown = weapon->fireRate;
        }
        
        weapon->fire = false;
	}
}
