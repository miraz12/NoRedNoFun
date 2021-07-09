#include "System.h"

class ECSManager;
class MovementSystem : public System
{
public:

	MovementSystem(ECSManager *ECSManager);

	void update(float dt);

};