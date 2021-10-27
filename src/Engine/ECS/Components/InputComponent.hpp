#pragma once
#include "Component.hpp"

#include <GLFW/glfw3.h>

class InputComponent: public Component
{
public:
	int keys[1024];
	double mouseX;
	double mouseY;
	bool rotateTowardsMouse;

	int winWidth;
	int winHeight;

	InputComponent(GLFWwindow* window);

	void calculateInput();

private:
	GLFWwindow* m_window;
	bool manualInput{false};
};

