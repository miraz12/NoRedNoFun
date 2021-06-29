#pragma once
#include "Component.h"
#include <GLFW/glfw3.h>

class InputComponent: public Component
{
public:
	int m_keys[1024];

	InputComponent(GLFWwindow* window);

	void calculateInput();

	ComponentTypeEnum getComponentType();

private:
	GLFWwindow* m_window;
};

