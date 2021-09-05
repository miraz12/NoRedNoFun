#include "Component.h"

#include <glm/glm.hpp>

#include "../../Engine/Objects/Quad.hpp"

class InstancedQuadManager;

class PositionComponent : public Component 
{

public:
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;
	Quad* quad;
	InstancedQuadManager* quadManager;

	PositionComponent(Quad* aQuad, InstancedQuadManager* aQuadManager);
	virtual ~PositionComponent();
};