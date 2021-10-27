#include "CollisionComponent.hpp"

CollisionComponent::CollisionComponent() :
	isConstraint(false),
	effectMovement(true),
	allowedClimbing(0.5f) {
	shape.addNormal(glm::vec2(1.0f, 0.0f));
	shape.addNormal(glm::vec2(0.0f, 1.0f));

	shape.addVertex(glm::vec2(-0.5f, -0.5f));
	shape.addVertex(glm::vec2(0.5f, -0.5f));
	shape.addVertex(glm::vec2(-0.5f, 0.5f));
	shape.addVertex(glm::vec2(0.5f, 0.5f));

	shape.setTransformMatrix(glm::mat4(1.0f));

	m_componentType = ComponentTypeEnum::COLLISION;
}
