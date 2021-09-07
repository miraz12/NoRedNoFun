#include "InputComponent.h"


InputComponent::InputComponent(GLFWwindow* window)
	: keys(), mouseX(0.0), mouseY(0.0), m_window(window){

	glfwGetWindowSize(m_window, &winWidth, &winHeight);
	m_componentType = ComponentTypeEnum::INPUT;
}

void InputComponent::updateInput(unsigned int key) {
	manualInput = true;
	keys[GLFW_KEY_W] = 0;
	keys[GLFW_KEY_A] = 0;
	keys[GLFW_KEY_S] = 0;
	keys[GLFW_KEY_D] = 0;
	switch (key)
	{
	case 0:
		keys[GLFW_KEY_W] = 1;
		break;
	case 1: 
		keys[GLFW_KEY_A] = 1;
		break;
	case 2: 
		keys[GLFW_KEY_S] = 1;
		break;
	case 3:
		keys[GLFW_KEY_D] = 1;
		break;
	default:
		break;
	}
};
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
