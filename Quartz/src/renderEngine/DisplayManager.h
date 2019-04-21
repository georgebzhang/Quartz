#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DisplayManager {
public:
	void open();
	bool isActive();
	void update();
	void close();

private:
	GLFWwindow* window;
};