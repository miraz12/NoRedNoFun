#include "GraphicsComponent.h"

#include "../../Engine/Objects/InstancedQuadManager.hpp"

GraphicsComponent::GraphicsComponent(Quad* aQuad, InstancedQuadManager* aQuadManager) :
	quad(aQuad),
	quadManager(aQuadManager) {

	m_componentType = ComponentTypeEnum::GRAPHICS;
}

GraphicsComponent::~GraphicsComponent() {
	quadManager->returnQuad(quad);
}
