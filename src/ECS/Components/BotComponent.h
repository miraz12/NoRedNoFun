#pragma once
#include "Component.h"
#include "../../../resources/Bots/BotInterface.hpp"
class BotComponent : public Component
{
public:
    BotComponent() = delete;
    BotComponent(BotInterface* botInterface);

    void activateBot(float dt);

private:
    BotInterface* m_botInterface;
};