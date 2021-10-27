#include "AnimationSystem.hpp"
#include "ECS/Components/GraphicsComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"

#include <algorithm>

AnimationSystem::AnimationSystem(ECSManager* ECSManager) 
: System(ECSManager, ComponentTypeEnum::GRAPHICS){

}

void AnimationSystem::update(float dt) {
	//System should only have one entity
	for (auto& e : m_entities) {
		GraphicsComponent* graphComp = static_cast<GraphicsComponent*>(e->getComponent(ComponentTypeEnum::GRAPHICS));
		if (!graphComp->animate) {
			continue;
		}

		MovementComponent* movComp = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));

		graphComp->updateTimer += dt;
		float totUpdateInterval = graphComp->updateInterval;

		if (movComp && graphComp->movementMultiplier != 0.0f) {
			totUpdateInterval = graphComp->updateInterval / std::max(movComp->velocity.x * graphComp->movementMultiplier, 1.0f); 
		}

		graphComp->advancements += (int)std::floor(graphComp->updateTimer / std::max(totUpdateInterval, 0.00001f));
		graphComp->updateTimer = std::fmod(graphComp->updateTimer, std::max(totUpdateInterval, 0.00001f));

        float xAdvance = std::fmod((graphComp->advanceBy.x * graphComp->advancements), std::max(graphComp->modAdvancement.x, 1.0f));
        float yAdvance = std::fmod((graphComp->advanceBy.y * graphComp->advancements), std::max(graphComp->modAdvancement.y, 1.0f));
        graphComp->quad->setCurrentSprite(graphComp->startingTile.x + xAdvance, graphComp->startingTile.y + yAdvance);
	}
}