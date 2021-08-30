#include "PositionComponent.h"


PositionComponent::PositionComponent(Quad* aQuad, float startX, float startY) :
	position(startX, startY, -0.1f),
	rotation(0.0f),
	scale(1.0f), 
	quad(aQuad){

	m_componentType = ComponentTypeEnum::POSITION;
}
