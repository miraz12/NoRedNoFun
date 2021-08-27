#include "Component.h"

class HealthComponent : public Component 
{

public:
	HealthComponent();
	void damage(unsigned int hp);
	void heal(unsigned int hp);
private:
	int health;
};