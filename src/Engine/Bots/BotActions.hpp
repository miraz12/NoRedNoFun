#include "ECS/ECSManager.hpp"
#include "ECS/Components/WeaponComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "ECS/Components/BotComponent.hpp"
#include "Rendering.hpp"
#include "Window.hpp"

namespace BotActions {

void botMove(unsigned int key, BotInterface* bot)
{
	Entity* e = ECSManager::getInstance().getEntity(bot->m_id);
	BotComponent* botC = static_cast<BotComponent*>(e->getComponent(ComponentTypeEnum::BOT));
	
	action a;
	a.data.key = key;
	a.type = aType::move;
	botC->addAction(a);
	
}

void botFire(BotInterface* bot) {
//	Entity* e = ECSManager::getEntity(bot->m_id);
//	if (e) {
//		WeaponComponent* weaponComp = static_cast<WeaponComponent*>(e->getComponent(ComponentTypeEnum::WEAPON));
//		if (weaponComp) {
//			weaponComp->fire = true;
//		}
//	}
}

void botLookAt(int x, int y, BotInterface* bot){
	//Entity* e = ECSManager::getEntity(bot->m_id);
	//if (e) {
	//	PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
	//	if (p) {
	//		p->rotation = ::atan2f(static_cast<float>(x - p->position.x), static_cast<float>(p->position.y - y));
	//	}
	//}
}

}