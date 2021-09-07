#pragma once
#include "Component.hpp"
#include "../../Physics/Shape.hpp"

class Entity;

class CollisionComponent : public Component
{
public:
	Shape shape;
	std::vector<Entity*> currentCollisionEntities; //List of collisions happening right now (this frame)
	bool effectMovement;

	CollisionComponent();
};

