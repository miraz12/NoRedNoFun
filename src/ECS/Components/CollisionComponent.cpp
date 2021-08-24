#include "CollisionComponent.h"

CollisionComponent::CollisionComponent()
	{
	shape.addNormal(glm::vec2(1.0f, 0.0f));
	shape.addNormal(glm::vec2(0.0f, 1.0f));

	shape.addVertex(glm::vec2(-0.5f, -0.5f));
	shape.addVertex(glm::vec2(0.5f, -0.5f));
	shape.addVertex(glm::vec2(-0.5f, 0.5f));
	shape.addVertex(glm::vec2(0.5f, 0.5f));

	shape.setTransformMatrix(glm::mat4(1.0f));

	m_componentType = ComponentTypeEnum::COLLISION;
}
