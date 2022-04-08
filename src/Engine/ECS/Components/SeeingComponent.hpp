#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>
#include <vector>

class Entity;

class SeeingComponent : public Component
{
public:
    float fov;
    unsigned int nrOfRays;
    float viewDistance;

	SeeingComponent();
};

