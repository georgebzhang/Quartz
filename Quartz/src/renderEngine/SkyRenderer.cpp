#include "SkyRenderer.h"

SkyRenderer::SkyRenderer(Shader* shader, const glm::mat4& projectionMatrix) : m_Shader(shader) {
	m_Shader->bind();
	m_Shader->setUniformMat4f("u_ProjectionMatrix", projectionMatrix);
	m_Shader->unbind();
}

void SkyRenderer::render(CubeMapModel* sky) const {
	CubeMap* cubeMap = sky->getCubeMap();
	cubeMap->bind();
	m_Shader->setUniform1i("u_SkyBox", 0);
	RawModel* rawModel = sky->getRawModel();
	rawModel->getVA()->bind();
	GLCall(glEnableVertexAttribArray(0));

	GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
	//GLCall(glDrawElements(GL_TRIANGLES, rawModel->getIB()->getCount(), GL_UNSIGNED_INT, (const void*)0));

	//cubeMap->unbind();
	GLCall(glDisableVertexAttribArray(0));
	rawModel->getVA()->unbind();
}
