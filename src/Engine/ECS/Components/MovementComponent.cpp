#include "MovementComponent.hpp"
#include "MapLoader/MapLoader.hpp"

MovementComponent::MovementComponent() :
	accelerationDirection(0.0f),
	velocity(0.0f),
	acceleration(20.0f),
	drag(10.0f),
	maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}

MovementComponent::MovementComponent(float velX, float velY) :
	accelerationDirection(0.0f),
	velocity(velX, velY, 0.0f),
	acceleration(20.0f),
	drag(10.0f),
	maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}
