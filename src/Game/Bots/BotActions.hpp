#include "../../ECS/ECSManager.h"
namespace BotActions {

void botMove(unsigned int key, BotInterface* bot)
{
	Entity *e = ECSManager::getEntity(bot->m_id);
	if (e) {
		static_cast<InputComponent*>(e->getComponent(ComponentTypeEnum::INPUT))->updateInput(key);
	}
}

}