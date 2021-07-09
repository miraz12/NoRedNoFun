#include "MovementComponent.h"
#include "../../Engine/MapLoader/MapLoader.hpp"

MovementComponent::MovementComponent() :
	m_accelerationDirection(0.0f),
	m_velocity(0.0f),
	m_acceleration(20.0f),
	m_drag(10.0f),
	m_maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}
