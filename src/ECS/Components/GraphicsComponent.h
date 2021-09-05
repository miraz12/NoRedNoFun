#include "Component.h"

#include <glm/glm.hpp>

#include "../../Engine/Objects/Quad.hpp"

class GraphicsComponent : public Component 
{

public:
	Quad* quad;

	GraphicsComponent();
	virtual ~GraphicsComponent();
};