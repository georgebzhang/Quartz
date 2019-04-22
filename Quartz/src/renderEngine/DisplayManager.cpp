#include "DisplayManager.h"

#include <iostream>

void DisplayManager::open() {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640*2, 480*2, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "GLEW Error!" << std::endl;
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
