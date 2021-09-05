#include "PositionComponent.h"

#include "../../Engine/Objects/InstancedQuadManager.hpp"

PositionComponent::PositionComponent(Quad* aQuad, InstancedQuadManager* aQuadManager) :
	position(2.0f, 2.0f, -0.1f),
	rotation(0.0f),
	scale(1.0f), 
	quad(aQuad),
	quadManager(aQuadManager) {

	m_componentType = ComponentTypeEnum::POSITION;
}

PositionComponent::PositionComponent(Quad* aQuad, InstancedQuadManager* aQuadManager, float startX, float startY) :
	position(startX, startY, -0.1f),
	rotation(0.0f),
	scale(1.0f),
	quad(aQuad),
	quadManager(aQuadManager) {
	m_componentType = ComponentTypeEnum::POSITION;
}

PositionComponent::~PositionComponent() {
	quadManager->returnQuad(quad);
}
