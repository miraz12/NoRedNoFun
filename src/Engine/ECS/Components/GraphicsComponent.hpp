#include "Component.hpp"

#include "Objects/Quad.hpp"

class GraphicsComponent : public Component 
{

public:
	Quad* quad;

	GraphicsComponent();
	virtual ~GraphicsComponent();
};