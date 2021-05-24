#include "PositionComponent.h"



PositionComponent::PositionComponent() :
	m_xPosition(0.0f), m_yPosition(0.0f){
}
PositionComponent::PositionComponent(float x, float y) :
	m_xPosition(x), m_yPosition(y) {
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
