#include "PositionComponent.h"



PositionComponent::PositionComponent(Quad* aQuad) :
	position(2.0f, 2.0f, -0.1f),
	rotation(0.0f),
	scale(1.0f), 
	m_xPosition(0.0f), m_yPosition(0.0f),
	quad(aQuad){
	m_componentType = ComponentTypeEnum::POSITION;
}


void PositionComponent::setPositionX(float x) {
	m_xPosition = x;
}
void PositionComponent::setPositionY(float y) {
	m_yPosition = y;
}


float& PositionComponent::getPositionX() {
	return m_xPosition;
}
float& PositionComponent::getPositionY() {
	return m_yPosition;
}
