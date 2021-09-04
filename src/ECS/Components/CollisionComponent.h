#pragma once
#include "Component.h"
#include "../../Engine/Physics/Shape.hpp"

class Entity;

class CollisionComponent : public Component
{
public:
	Shape shape;
	std::vector<Entity*> currentCollisionEntities; //List of collisions happening right now (this frame)

	CollisionComponent();
};

