#include "Component.h"

#include <glm/glm.hpp>

#include "../../Engine/Objects/Quad.hpp"

class PositionComponent : public Component 
{

public:
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;
	Quad* quad;

	PositionComponent(Quad* aQuad);
	PositionComponent(Quad* aQuad, float startX, float startY);
};