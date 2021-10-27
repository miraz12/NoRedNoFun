#include "GraphicsComponent.hpp"
#include "Rendering.hpp"

#include "Objects/InstancedQuadManager.hpp"

GraphicsComponent::GraphicsComponent():
	animate(false),
	startingTile(0.0f),
	advanceBy(0.0f),
	updateInterval(1.0f),
	modAdvancement(1.0f),
	updateTimer(0.0f),
	movementMultiplier(0.0f),
	advancements(0) {
	quad = Rendering::getInstance().getNewQuad();

	m_componentType = ComponentTypeEnum::GRAPHICS;
}

GraphicsComponent::~GraphicsComponent() {
	Rendering::getInstance().getQuadManager()->returnQuad(quad);
}
