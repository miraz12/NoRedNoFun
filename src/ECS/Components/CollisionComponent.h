#pragma once
#include "Component.h"
#include "../../Engine/Physics/Shape.hpp"

class CollisionComponent : public Component
{
public:
	Shape shape;

	CollisionComponent();
};

