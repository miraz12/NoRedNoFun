#include "ECS/Components/BotComponent.hpp"

BotComponent::BotComponent() {
    m_componentType = ComponentTypeEnum::BOT;
    actions.reserve(1000);
}

void BotComponent::addAction(action a) {
    actions.push_back(a);
}

std::vector<action>& BotComponent::getActions() {
    return actions;
}