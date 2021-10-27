#include "Component.hpp"

#include "Engine/Objects/Quad.hpp"

class GraphicsComponent : public Component 
{

public:
	Quad* quad;

	bool animate;
	glm::vec2 startingTile;
	glm::vec2 advanceBy;
	float updateInterval;
	glm::vec2 modAdvancement;
	float updateTimer;
	float movementMultiplier;
	int advancements;

	GraphicsComponent();
	virtual ~GraphicsComponent();
};
