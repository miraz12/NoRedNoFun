#include "MovementComponent.h"
#include "../../Engine/MapLoader/MapLoader.hpp"

MovementComponent::MovementComponent() :
	accelerationDirection(0.0f),
	velocity(0.0f),
	acceleration(20.0f),
	drag(10.0f),
	maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}
