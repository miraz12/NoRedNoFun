#include "Component.h"
#include <glm/glm.hpp>

class PositionComponent : public Component 
{

public:
	glm::vec3 m_position;
	float m_rotation;
	glm::vec3 m_scale;
	glm::mat4& m_matrix;

	PositionComponent(glm::mat4& modelMatrix);
	//PositionComponent(float x, float y);

	void setPositionX(float x);
	void setPositionY(float y);

	float& getPositionX();
	float& getPositionY();

private:
	float m_xPosition;
	float m_yPosition;
};