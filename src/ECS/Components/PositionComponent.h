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

	void setPositionX(float x);
	void setPositionY(float y);

	float& getPositionX();
	float& getPositionY();

private:
	float m_xPosition;
	float m_yPosition;
};