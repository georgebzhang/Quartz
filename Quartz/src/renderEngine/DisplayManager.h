#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../entities/Camera.h"

class DisplayManager {
public:
	DisplayManager() {}
	~DisplayManager() {}

	void open();
	bool isOpen() { return !glfwWindowShouldClose(m_Window); }
	void finishLoop();
	void close() { glfwTerminate(); }

private:
	GLFWwindow* m_Window;
	const int WIDTH = 640 * 2;
	const int HEIGHT = 480 * 2;
};