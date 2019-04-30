#include "Camera.h"
#include "../toolbox/Maths.h"

void Camera::translate(const glm::vec3 translation) {
	m_Position += translation;
}

void Camera::loadUniforms(Shader* shader) const {
	shader->setUniform3fv("u_CamPosition", m_Position);
	glm::mat4 viewMatrix = Maths::createViewMatrix(this);
	shader->setUniformMat4f("u_ViewMatrix", viewMatrix);
}
