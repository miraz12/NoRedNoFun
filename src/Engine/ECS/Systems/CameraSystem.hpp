#pragma once
#include "System.hpp"

class CameraSystem : public System
{
public:
	CameraSystem(ECSManager* ECSManager);

	void update(float dt);

};

