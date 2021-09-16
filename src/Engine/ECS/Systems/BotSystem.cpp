#include "ECS/Systems/BotSystem.hpp"
#include "ECS/Components/BotComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"

#include <glm/glm.hpp>

BotSystem::BotSystem(ECSManager* ECSManager) : System(ECSManager, ComponentTypeEnum::MOVEMENT) {

}

void BotSystem::update(float dt) {
    for(auto& e : m_entities) {
		BotComponent* botC = static_cast<BotComponent*>(e->getComponent(ComponentTypeEnum::BOT));

        if (botC) {
            for (unsigned int i = 0; i < botC->getActions().size(); i++) {
                action a = botC->getActions().back();
                botC->getActions().pop_back();
                MovementComponent* movement = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));
                if(movement) {
                    glm::vec3 direction(0.0f);
                    switch (a.data.key) {
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
        }
    }
}