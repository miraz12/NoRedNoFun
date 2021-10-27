#include "InputComponent.hpp"


InputComponent::InputComponent(GLFWwindow* window)
	: keys(), mouseX(150.0), mouseY(650.0), rotateTowardsMouse(true), m_window(window){

	glfwGetWindowSize(m_window, &winWidth, &winHeight);
	m_componentType = ComponentTypeEnum::INPUT;
}

void InputComponent::calculateInput() {
	if(!manualInput) {
		keys[GLFW_KEY_W] = glfwGetKey(m_window, GLFW_KEY_W);
		keys[GLFW_KEY_S] = glfwGetKey(m_window, GLFW_KEY_S);
		keys[GLFW_KEY_A] = glfwGetKey(m_window, GLFW_KEY_A);
		keys[GLFW_KEY_D] = glfwGetKey(m_window, GLFW_KEY_D);
		keys[GLFW_KEY_SPACE] = glfwGetKey(m_window, GLFW_KEY_SPACE);
		glfwGetCursorPos(m_window, &mouseX, &mouseY);
		glfwGetWindowSize(m_window, &winWidth, &winHeight);
	}
}
