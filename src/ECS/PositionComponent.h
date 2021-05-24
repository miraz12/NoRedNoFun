#include "Component.h"

class PositionComponent : public Component 
{

public:
	PositionComponent();
	PositionComponent(float x, float y);

	void setPositionX(float x);
	void setPositionY(float y);

	float& getPositionX();
	float& getPositionY();

private:
	float m_xPosition;
	float m_yPosition;
};