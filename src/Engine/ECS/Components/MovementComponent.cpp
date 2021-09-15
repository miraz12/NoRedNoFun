#include "MovementComponent.hpp"
#include "MapLoader/MapLoader.hpp"

MovementComponent::MovementComponent() :
	velocity(0.0f),
	acceleration(20.0f),
	drag(10.0f),
	maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}

MovementComponent::MovementComponent(float velX, float velY) :
	velocity(velX, velY, 0.0f),
	acceleration(20.0f),
	drag(10.0f),
	maxSpeed(7.0f){
	m_componentType = ComponentTypeEnum::MOVEMENT;
}
