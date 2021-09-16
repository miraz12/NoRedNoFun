#include "SeeingComponent.hpp"

SeeingComponent::SeeingComponent(): fov(70.0f), nrOfRays(10), viewDistance(10.0f) {
	m_componentType = ComponentTypeEnum::SEEING;
}
