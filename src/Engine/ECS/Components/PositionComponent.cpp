#include "PositionComponent.hpp"

#include <glm/ext.hpp>

PositionComponent::PositionComponent() :
	position(2.0f, 2.0f, -0.1f),
	rotation(0.0f),
	scale(1.0f) {
	m_componentType = ComponentTypeEnum::POSITION;
}

PositionComponent::PositionComponent(float startX, float startY) :
	position(startX, startY, -0.1f),
	rotation(0.0f),
	scale(1.0f) {
	m_componentType = ComponentTypeEnum::POSITION;
}

glm::mat4 PositionComponent::calculateMatrix() {
	glm::mat4 tempMatrix = glm::translate(glm::mat4(1.0f), position);
	tempMatrix = glm::rotate(tempMatrix, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
	tempMatrix = glm::scale(tempMatrix, scale);

	return tempMatrix;
}