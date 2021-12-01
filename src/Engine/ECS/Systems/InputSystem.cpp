#include "InputSystem.hpp"
#include "ECS/Components/InputComponent.hpp"
#include "ECS/Components/MovementComponent.hpp"
#include "ECS/ECSManager.hpp"

#include "ECS/Components/WeaponComponent.hpp"
#include "ECS/Components/PositionComponent.hpp"


InputSystem::InputSystem(ECSManager *ECSManager) 
	: System(ECSManager, ComponentTypeEnum::INPUT, ComponentTypeEnum::MOVEMENT){
}


void InputSystem::update(float /*dt*/){
	//Handle input


	for (auto& e : m_entities) {
		//Get component(s)
		InputComponent* input = static_cast<InputComponent*>(e->getComponent(ComponentTypeEnum::INPUT));
		MovementComponent* movement = static_cast<MovementComponent*>(e->getComponent(ComponentTypeEnum::MOVEMENT));

		//calculate input. Maybe every AI can use its own input component for this?
		input->calculateInput();

		//movementInput
		glm::vec3 direction(0.0f);
		if (input->keys[GLFW_KEY_W] == GLFW_PRESS) {
			direction.y += 1.0f;
		}
		if (input->keys[GLFW_KEY_S] == GLFW_PRESS) {
			direction.y += -1.0f;
		}
		if (input->keys[GLFW_KEY_A] == GLFW_PRESS) {
			direction.x += -1.0f;
		}
		if (input->keys[GLFW_KEY_D] == GLFW_PRESS) {
			direction.x += 1.0f;
		}
		if (input->keys[GLFW_KEY_SPACE] == GLFW_PRESS) {
			// m_manager->removeComponent(*e, ComponentTypeEnum::COLLISION);
			WeaponComponent* weaponComp = static_cast<WeaponComponent*>(e->getComponent(ComponentTypeEnum::WEAPON));
			if (weaponComp) {
				weaponComp->fire = true;
			}
		}
		movement->accelerationDirection.x = direction.x;
		movement->accelerationDirection.y = direction.y;

		PositionComponent* p = static_cast<PositionComponent*>(e->getComponent(ComponentTypeEnum::POSITION));
		if (p) {
			glm::vec2 temp = glm::inverse(ECSManager::getInstance().getGraphicsSystem()->getCamera()->getViewMatrix()) * 
				glm::vec4((input->mouseX / input->winWidth) * 2.0f - 1.0f, ((input->winHeight - input->mouseY) / input->winHeight) * 2.0f - 1.0f, 0.0f, 1.0f);
			p->rotation = ::atan2f(temp.x - p->position.x , p->position.y - temp.y);
		}
	}
}