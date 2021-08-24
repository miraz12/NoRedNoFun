#include "InputComponent.h"


InputComponent::InputComponent(GLFWwindow* window)
	: keys(), m_window(window){
	m_componentType = ComponentTypeEnum::INPUT;
}


void InputComponent::calculateInput() {
	keys[GLFW_KEY_W] = glfwGetKey(m_window, GLFW_KEY_W);
	keys[GLFW_KEY_S] = glfwGetKey(m_window, GLFW_KEY_S);
	keys[GLFW_KEY_A] = glfwGetKey(m_window, GLFW_KEY_A);
	keys[GLFW_KEY_D] = glfwGetKey(m_window, GLFW_KEY_D);
	keys[GLFW_KEY_SPACE] = glfwGetKey(m_window, GLFW_KEY_SPACE);
}
