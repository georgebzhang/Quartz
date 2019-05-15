#include "DisplayManager.h"
#include "../entities/Camera.h"

#include <iostream>

GLFWwindow* DisplayManager::m_Window;
float DisplayManager::m_LastFrameTime = 0.0f;
float DisplayManager::m_DeltaTime = 0.0f;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

void DisplayManager::open() {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	m_Window = glfwCreateWindow(WIDTH, HEIGHT, "CS284A Bubble Simulator", NULL, NULL);
	if (!m_Window)
	{
		glfwTerminate();
		return;
	}

	glfwSetKeyCallback(m_Window, keyCallback);
	glfwSetInputMode(m_Window, GLFW_STICKY_KEYS, GLFW_TRUE);

	glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
	glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
	glfwSetScrollCallback(m_Window, scrollCallback);

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting OpenGL profile to CORE instead of COMPAT

	/* Make the window's context current */
	glfwMakeContextCurrent(m_Window);

	glfwSwapInterval(1); // synchronize with monitor refresh rate

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	m_LastFrameTime = glfwGetTime();
}

void DisplayManager::finishLoop() {
	// rendering moved to main

	glEnd();

	/* Swap front and back buffers */
	glfwSwapBuffers(m_Window);

	/* Poll for and process events */
	glfwPollEvents();

	float currentFrameTime = glfwGetTime();
	m_DeltaTime = currentFrameTime - m_LastFrameTime;
	m_LastFrameTime = currentFrameTime;
}