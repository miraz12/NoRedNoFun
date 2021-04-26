#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "TestDir/Test.hpp"

int main() {
	std::cout << "Hello world!\n";

	Test test;

	if (!glfwInit()) return false;
	
	std::getchar();
	return 0;
}
