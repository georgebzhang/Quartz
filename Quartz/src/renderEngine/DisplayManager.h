#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>

#include "../entities/Camera.h"

class DisplayManager {
public:
	static void open();
	static bool isOpen() { return !glfwWindowShouldClose(m_Window); }
	static void finishLoop();
	static void close() { glfwTerminate(); }

	inline static float getFrameDuration() { return delta.count(); }

private:
	static GLFWwindow* m_Window;
	static const int DIM_SCALE = 2;
	static const int WIDTH = 640 * DIM_SCALE;
	static const int HEIGHT = 480 * DIM_SCALE;

	static std::chrono::time_point<std::chrono::steady_clock> lastFrameTime;
	static std::chrono::duration<float> delta;
};