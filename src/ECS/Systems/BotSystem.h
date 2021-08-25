#pragma once
#include "System.h"
class BotSystem : public System
{
public:
	BotSystem() = delete;
	BotSystem(ECSManager* ECSManager);

	void update(float dt);
};

