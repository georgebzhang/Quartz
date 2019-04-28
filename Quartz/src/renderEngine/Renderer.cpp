#include "../errors/ErrorHandler.h"
#include "Renderer.h"

#include <GL/glew.h>

void Renderer::prepare() {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1, 0, 0, 1));
}

void Renderer::render(RawModel model) {
//void Renderer::render(TexturedModel texturedModel) {
	//RawModel model = texturedModel.getRawModel();
	GLCall(glBindVertexArray(model.getVAOID()));
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));

	//GLCall(texturedModel.getTexture().Bind());

	//glDrawArrays(GL_TRIANGLES, 0, model.getVertexCount());
	GLCall(glDrawElements(GL_TRIANGLES, model.getVertexCount(), GL_UNSIGNED_INT, (const void*) 0));

	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	GLCall(glBindVertexArray(0));
}