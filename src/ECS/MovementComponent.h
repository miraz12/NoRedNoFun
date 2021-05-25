#include "Component.h"
#include <glm/glm.hpp>

class MovementComponent : public Component
{
public:
	MovementComponent();

	//updates position x and y based on velocity and delta time dt
	void move(float dt, float &x, float &y);

	void setVelocity(glm::vec2 v);

private:
	glm::vec2 m_velocity;
};