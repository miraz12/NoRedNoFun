#include "BotComponent.h"

BotComponent::BotComponent(BotInterface* botInterface)
	: m_botInterface(botInterface) {
	m_componentType = ComponentTypeEnum::BOT;
}

void BotComponent::activateBot(float dt) {
	m_botInterface->print();
}