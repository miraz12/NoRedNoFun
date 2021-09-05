#pragma once
#include "System.h"

class GraphicsSystem : public System
{
public:

	GraphicsSystem(ECSManager *ECSManager);

	void update(float dt);

};