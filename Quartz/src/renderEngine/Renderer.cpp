#include "../errors/ErrorHandler.h"
#include "Renderer.h"
#include "../toolbox/Maths.h"

#include <GL/glew.h>

void Renderer::prepare() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
	GLCall(glClearColor(1, 0, 0, 1));
}

//void Renderer::render(const RawModel* model) const {
//void Renderer::render(const TexturedModel* texturedModel) const {
void Renderer::render(const Entity* entity, Shader* shader) const {
//	std::cout << &(texturedModel.getRawModel()) << std::endl;
//	std::cout << texturedModel.getRawModel().getVAOID() << std::endl;
//	std::cout << texturedModel.getRawModel().getVertexCount() << std::endl;
	TexturedModel* texturedModel = entity->getTexturedModel();
	RawModel* rawModel = texturedModel->getRawModel();
	rawModel->getVA()->bind();
	rawModel->getIB()->bind();
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glEnableVertexAttribArray(1));

	glm::mat4 transformationMatrix = Maths::createTransformationMatrix(entity->getPosition(), entity->getRotation(), entity->getScale());
	shader->setUniformMat4f("u_TransformationMatrix", transformationMatrix);

	GLCall(glDrawElements(GL_TRIANGLES, rawModel->getIB()->getCount(), GL_UNSIGNED_INT, (const void*) 0));
	GLCall(glDisableVertexAttribArray(0));
	GLCall(glDisableVertexAttribArray(1));
	rawModel->getIB()->unbind();
	rawModel->getVA()->unbind();
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
