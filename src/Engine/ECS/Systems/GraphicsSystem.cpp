#include "GraphicsSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/GraphicsComponent.hpp"

#include "Rendering.hpp"

GraphicsSystem::GraphicsSystem(ECSManager * ECSManager) 
	: System(ECSManager, ComponentTypeEnum::POSITION, ComponentTypeEnum::GRAPHICS){

}

void GraphicsSystem::update(float /*dt*/)
{
	for (auto& e : m_entities) {
		PositionComponent *p = static_cast<PositionComponent *>(e->getComponent(ComponentTypeEnum::POSITION));
		GraphicsComponent *g = static_cast<GraphicsComponent*>(e->getComponent(ComponentTypeEnum::GRAPHICS));

        g->quad->getModelMatrix() = p->calculateMatrix();
	}
}
