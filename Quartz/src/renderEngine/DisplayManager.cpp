#include "DisplayManager.h"
#include "../entities/Camera.h"

#include <iostream>

GLFWwindow* DisplayManager::m_Window;
std::chrono::time_point<std::chrono::steady_clock> DisplayManager::lastFrameTime;
std::chrono::duration<float> DisplayManager::delta;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

void DisplayManager::open() {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(m_Window, keyCallback);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

	//glfwSetCursorPosCallback(m_Window, cursorPositionCallback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting OpenGL profile to CORE instead of COMPAT

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	glfwSwapInterval(1); // synchronize with monitor refresh rate

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	lastFrameTime = std::chrono::high_resolution_clock::now();
}

void DisplayManager::finishLoop() {
	// rendering moved to main

	glEnd();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);

	/* Poll for and process events */
	glfwPollEvents();

	auto currentFrameTime = std::chrono::high_resolution_clock::now();
	delta = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;
}