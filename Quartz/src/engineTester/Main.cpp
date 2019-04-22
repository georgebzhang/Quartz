#include "../renderEngine/DisplayManager.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/Renderer.h"

int main(void)
{
	DisplayManager dm;

	dm.open();

	Loader loader;
	Renderer renderer;

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
	};

	int count = sizeof(vertices) / sizeof(vertices[0]);
	RawModel model = loader.loadToVAO(vertices, count);

	while (dm.isActive()) {
		/* Render here */
		renderer.prepare();
		renderer.render(model);

		dm.update();
	}

	loader.cleanUp();

	dm.close();
}