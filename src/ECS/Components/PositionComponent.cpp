#include "PositionComponent.h"



PositionComponent::PositionComponent(glm::mat4& modelMatrix) :
	m_position(2.0f, 2.0f, -0.1f),
	m_rotation(0.0f),
	m_scale(1.0f), 
	m_matrix(modelMatrix){
	m_componentType = ComponentTypeEnum::POSITION;
}
