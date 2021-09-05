#include "Component.h"

#include <glm/glm.hpp>

#include "../../Engine/Objects/Quad.hpp"

class InstancedQuadManager;

class GraphicsComponent : public Component 
{

public:
	Quad* quad;
	InstancedQuadManager* quadManager;

	GraphicsComponent(Quad* aQuad, InstancedQuadManager* aQuadManager);
	virtual ~GraphicsComponent();
};