#include "ECS/ECSManager.hpp"
#include "ECS/Components/WeaponComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"
#include "Window.hpp"

namespace BotActions {

void botMove(unsigned int key, BotInterface* bot)
{
	Entity* e = ECSManager::getEntity(bot->m_id);
	if (e) {
		MovementComponent* movement = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));
		//movementInput
		glm::vec3 direction(0.0f);
		switch (key) {
			case 0:
				direction.y += 1.0f;
				break;
			case 1: 
				direction.y += -1.0f;
				break;
			case 2: 
				direction.x += -1.0f;
				break;
			case 3:
				direction.x += 1.0f;
				break;
			case 4: 
			default:
				break;
		}
		movement->accelerationDirection.x = direction.x;
		movement->accelerationDirection.y = direction.y;
	}
}

void botFire(BotInterface* bot) {
	Entity* e = ECSManager::getEntity(bot->m_id);
	if (e) {
		WeaponComponent* weaponComp = static_cast<WeaponComponent*>(e->getComponent(ComponentTypeEnum::WEAPON));
		if (weaponComp) {
			weaponComp->fire = true;
		}
	}
}

void botLookAt(int x, int y, BotInterface* bot){
	Entity* e = ECSManager::getEntity(bot->m_id);
	if (e) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		if (p) {
			p->rotation = ::atan2f(static_cast<float>(x - p->position.x), static_cast<float>(p->position.y - y));
		}
	}
}

void botLookInDirection(float x, float y, BotInterface* bot) {
	Entity* e = ECSManager::getEntity(bot->m_id);
	if (e) {
		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		if (p) {
			p->rotation = ::atan2f(x, -y);
		}
	}
}

}