#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
	{
	m_shape.addNormal(glm::vec2(1.0f, 0.0f));
	m_shape.addNormal(glm::vec2(0.0f, 1.0f));

	m_shape.addVertex(glm::vec2(-0.5f, -0.5f));
	m_shape.addVertex(glm::vec2(0.5f, -0.5f));
	m_shape.addVertex(glm::vec2(-0.5f, 0.5f));
	m_shape.addVertex(glm::vec2(0.5f, 0.5f));

	m_shape.setPosition(glm::vec2(0.0f));

	m_componentType = ComponentTypeEnum::COLLISION;
}
