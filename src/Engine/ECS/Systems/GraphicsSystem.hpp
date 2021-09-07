#pragma once
#include "System.hpp"

class GraphicsSystem : public System
{
public:

	GraphicsSystem(ECSManager *ECSManager);

	void update(float dt);

};