#pragma once

#include "Component.hpp"
#include "../../../resources/Bots/BotInterface.hpp"

#include <glm/glm.hpp>
#include <vector>

class Entity;

class SeeingComponent : public Component
{
public:
    float fov;
    unsigned int nrOfRays;
    float viewDistance;
	std::vector<VisualEntity> visualEntities; //List of entities that can be seen right now

	SeeingComponent();
};

