#pragma once
#include "System.hpp"

class BotSystem : public System {
public:
    BotSystem(ECSManager *ECSManager);
    void update(float dt);
}