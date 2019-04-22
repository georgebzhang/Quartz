#include "Renderer.h"

#include <GL/glew.h>

void Renderer::prepare() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1, 0, 0, 1);
}

void Renderer::render(RawModel model) {
	glBindVertexArray(model.getVAOID());
	glEnableVertexAttribArray(0);
	//glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, (const void*) 0);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}