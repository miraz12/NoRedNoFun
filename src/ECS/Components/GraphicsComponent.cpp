#include "GraphicsComponent.h"
#include "../../Engine/Rendering.hpp"

#include "../../Engine/Objects/InstancedQuadManager.hpp"

GraphicsComponent::GraphicsComponent() {
	quad = Rendering::getInstance().getNewQuad();

	m_componentType = ComponentTypeEnum::GRAPHICS;
}

GraphicsComponent::~GraphicsComponent() {
	Rendering::getInstance().getQuadManager()->returnQuad(quad);
}
