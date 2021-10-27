#include "Rendering.hpp"
#include "CameraSystem.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/CameraFocusComponent.hpp"

CameraSystem::CameraSystem(ECSManager* ECSManager) 
: System(ECSManager, ComponentTypeEnum::CAMERAFOCUS, ComponentTypeEnum::POSITION){

}

void CameraSystem::update(float dt) {
	//System should only have one entity
	for (auto& e : m_entities) {
		PositionComponent* posComp = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		CameraFocusComponent* camComp =  static_cast<CameraFocusComponent*>(e->getComponent(ComponentTypeEnum::CAMERAFOCUS));

		Rendering::getInstance().getCamera()->setPosition(
			posComp->position.x + camComp->offset.x, posComp->position.y + camComp->offset.y);
	}
}