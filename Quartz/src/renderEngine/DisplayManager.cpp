#include "DisplayManager.h"

#include <iostream>

GLFWwindow* DisplayManager::window;

void DisplayManager::open() {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // setting OpenGL profile to CORE instead of COMPAT

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); // synchronize with monitor refresh rate

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
}

bool DisplayManager::isActive() {
	return !glfwWindowShouldClose(window);
}

void DisplayManager::update() {
	// rendering moved to main

	glEnd();

	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}

void DisplayManager::close() {
	glfwTerminate();
}
