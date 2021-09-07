#pragma once
#include "Component.h"

#ifdef __WIN32
#include <windows.h>
#endif
#include <GLFW/glfw3.h>

class InputComponent: public Component
{
public:
	int keys[1024];

	InputComponent(GLFWwindow* window);

	void calculateInput();
	void updateInput(unsigned int key);

private:
	GLFWwindow* m_window;
	bool manualInput{false};
};

