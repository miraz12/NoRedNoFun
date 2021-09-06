#include "WeaponSystem.h"
#include "../Components/PositionComponent.h"
#include "../Components/WeaponComponent.h"
#include "../Components/GraphicsComponent.h"
#include "../Components/CollisionComponent.h"
#include "../Components/DamageComponent.h"

#include "../ECSManager.h"

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
            PositionComponent* tempPos = new PositionComponent(weapon->muzzlePosition.x, weapon->muzzlePosition.y);
            tempPos->scale = glm::vec3(0.3f, 0.3f, 1.0f);
			m_manager->addComponent(projectileEntity, tempPos);
			MovementComponent* tempMove = new MovementComponent();
            tempMove->maxSpeed = 40.0f;
            tempMove->velocity = {weapon->aimDirection.x * weapon->speed, weapon->aimDirection.y * weapon->speed, 0.0f};
            if (entityMov) {
                tempMove->velocity += entityMov->velocity;
            }
			tempMove->drag = 0.0f;
			m_manager->addComponent(projectileEntity, tempMove);
			m_manager->addComponent(projectileEntity, new CollisionComponent());
			m_manager->addComponent(projectileEntity, new GraphicsComponent());
            m_manager->addComponent(projectileEntity, new DamageComponent());

            weapon->cooldown = weapon->fireRate;
        }
        
        weapon->fire = false;
	}
}
