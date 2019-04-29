#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../entities/Camera.h"

class DisplayManager {
public:
	DisplayManager() {}
	~DisplayManager();

	void open();
	bool isActive();
	void finishLoop();
	void close();

private:
	GLFWwindow* m_Window;
	const int WIDTH = 640 * 2;
	const int HEIGHT = 480 * 2;
};