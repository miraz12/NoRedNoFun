#include "GraphicsComponent.hpp"

#include "Objects/InstancedQuadManager.hpp"
#include "ECS/ECSManager.hpp"

GraphicsComponent::GraphicsComponent():
	animate(false),
	startingTile(0.0f),
	advanceBy(0.0f),
	updateInterval(1.0f),
	modAdvancement(1.0f),
	updateTimer(0.0f),
	movementMultiplier(0.0f),
	advancements(0) {
	quad = ECSManager::getInstance().getGraphicsSystem()->getNewQuad();

	m_componentType = ComponentTypeEnum::GRAPHICS;
}

GraphicsComponent::~GraphicsComponent() {
	ECSManager::getInstance().getGraphicsSystem()->getQuadManager()->returnQuad(quad);
}
