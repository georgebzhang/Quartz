#include "SkyRenderer.h"

SkyRenderer::SkyRenderer(Shader* shader, const glm::mat4& projectionMatrix) : m_Shader(shader) {
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	m_Shader->unbind();
}

void SkyRenderer::render() const {

}
