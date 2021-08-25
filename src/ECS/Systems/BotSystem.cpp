#include "BotSystem.h"
#include "../Components/BotComponent.h"

BotSystem::BotSystem(ECSManager* ECSManager)
	: System(ECSManager, ComponentTypeEnum::BOT) {

	}

void BotSystem::update(float dt) {
	for (auto& e : m_entities) {
		BotComponent* b = static_cast<BotComponent*>(e->getComponent(ComponentTypeEnum::BOT));

		//activate bot
		b->activateBot(dt);
	}
}