#include "SeeingComponent.hpp"

SeeingComponent::SeeingComponent(): fov(70.0f), nrOfRays(10) {
	m_componentType = ComponentTypeEnum::SEEING;
}
