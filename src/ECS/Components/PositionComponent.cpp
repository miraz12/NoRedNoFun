#include "PositionComponent.h"


PositionComponent::PositionComponent(Quad* aQuad) :
	position(2.0f, 2.0f, -0.1f),
	rotation(0.0f),
	scale(1.0f), 
	quad(aQuad){

	m_componentType = ComponentTypeEnum::POSITION;
}
