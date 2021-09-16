#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>
#include <vector>

class Entity;

class SeeingComponent : public Component
{
public:
    struct VisualEntity {
        float distance;
        glm::vec2 rayDir;
        Entity* entityHit;
    };

    float fov;
    unsigned int nrOfRays; 
	std::vector<VisualEntity> visualEntities; //List of entities that can be seen right now

	SeeingComponent();
};

