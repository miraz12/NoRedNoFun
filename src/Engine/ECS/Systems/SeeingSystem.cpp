#include "SeeingSystem.hpp"
#include "Physics/SAT.hpp"
#include "ECS/Components/CollisionComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/SeeingComponent.hpp"

#include <glm/gtx/rotate_vector.hpp>
#include <iostream>


SeeingSystem::SeeingSystem(ECSManager *ECSManager)
	: System(ECSManager, ComponentTypeEnum::COLLISION, ComponentTypeEnum::POSITION) {

}


void SeeingSystem::update(float /*dt*/) {
	for (auto& e : m_entities) {
		SeeingComponent* seeingComp = static_cast<SeeingComponent*>(e->getComponent(ComponentTypeEnum::SEEING));
        PositionComponent* posComp = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
        if (!seeingComp) { // This entity does not see
            continue;
        }

        seeingComp->visualEntities.clear();

		// Check raycasts towards other entities
        float rayRotationIncrease = glm::radians(seeingComp->fov) / seeingComp->nrOfRays;
        for (unsigned int i = 0; i < seeingComp->nrOfRays; i++) {
            seeingComp->visualEntities.emplace_back();
            seeingComp->visualEntities.back().rayDir = glm::rotate(glm::vec2(0.0f, -1.0f), 
                posComp->rotation - glm::radians(seeingComp->fov) * 0.5f + ((float) i + 0.5f) * rayRotationIncrease);
            seeingComp->visualEntities.back().distance = seeingComp->viewDistance;
            seeingComp->visualEntities.back().entityHit = nullptr;

            for (auto& e2 : m_entities) {
                if (e->getID() == e2->getID()) {
                    continue;
                }

                CollisionComponent* c2 = static_cast<CollisionComponent*>(e2->getComponent(ComponentTypeEnum::COLLISION));

                float hitDistance = SAT::getRaycastIntersection(posComp->position, 
                    seeingComp->visualEntities.back().rayDir, c2->shape, seeingComp->visualEntities.back().distance);
                if (hitDistance >= 0.0f && hitDistance < seeingComp->visualEntities.back().distance) {
                    seeingComp->visualEntities.back().distance = hitDistance;
                    seeingComp->visualEntities.back().entityHit = e2;
                }
            }
        }
	}
}