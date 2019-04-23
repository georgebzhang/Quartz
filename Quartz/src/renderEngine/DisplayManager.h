#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class DisplayManager {
public:
	static void open();
	static bool isActive();
	static void update();
	static void close();

private:
	static GLFWwindow* window;
	static const int WIDTH = 640 * 2;
	static const int HEIGHT = 480 * 2;
};