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
		0.5f, 0.5f, 0.0f,
	};

	int indices[] = {
		0, 1, 3,
		3, 1, 2
	};

	int p_count = sizeof(vertices) / sizeof(vertices[0]);
	int i_count = sizeof(indices) / sizeof(indices[0]);

	RawModel model = loader.loadToVAO(vertices, p_count, indices, i_count);

	while (dm.isActive()) {
		/* Render here */
		renderer.prepare();
		renderer.render(model);

		dm.update();
	}

	loader.cleanUp();

	dm.close();
}