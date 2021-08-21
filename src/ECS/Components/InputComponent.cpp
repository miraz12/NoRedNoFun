#include "InputComponent.h"


InputComponent::InputComponent(GLFWwindow* window)
	: m_keys(), m_window(window){
	m_componentType = ComponentTypeEnum::INPUT;
}


void InputComponent::calculateInput() {
	m_keys[GLFW_KEY_W] = glfwGetKey(m_window, GLFW_KEY_W);
	m_keys[GLFW_KEY_S] = glfwGetKey(m_window, GLFW_KEY_S);
	m_keys[GLFW_KEY_A] = glfwGetKey(m_window, GLFW_KEY_A);
	m_keys[GLFW_KEY_D] = glfwGetKey(m_window, GLFW_KEY_D);
	m_keys[GLFW_KEY_SPACE] = glfwGetKey(m_window, GLFW_KEY_SPACE);
}
