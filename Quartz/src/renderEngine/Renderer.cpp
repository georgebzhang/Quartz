#include "../errors/ErrorHandler.h"
#include "Renderer.h"

#include <GL/glew.h>

void Renderer::prepare() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1, 0, 0, 1));
}

void Renderer::render(const RawModel* model) const {
//void Renderer::render(TexturedModel texturedModel) {
//	std::cout << &(texturedModel.getRawModel()) << std::endl;
//	std::cout << texturedModel.getRawModel().getVAOID() << std::endl;
//	std::cout << texturedModel.getRawModel().getVertexCount() << std::endl;
	//RawModel model = texturedModel.getRawModel();
	model->getVA()->bind();
	model->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glDrawElements(GL_TRIANGLES, model->getIB()->getCount(), GL_UNSIGNED_INT, (const void*) 0));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	model->getIB()->unbind();
	model->getVA()->unbind();
}

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.bind();
	va.bind();
	ib.bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, (const void*) 0));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	ib.unbind();
	va.unbind();
	shader.unbind();
}
