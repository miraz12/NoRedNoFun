#include "GraphicsComponent.hpp"
#include "../../Rendering.hpp"

#include "../../Objects/InstancedQuadManager.hpp"

GraphicsComponent::GraphicsComponent() {
	quad = Rendering::getInstance().getNewQuad();

	m_componentType = ComponentTypeEnum::GRAPHICS;
}

GraphicsComponent::~GraphicsComponent() {
	Rendering::getInstance().getQuadManager()->returnQuad(quad);
}
