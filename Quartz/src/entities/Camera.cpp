#include "Camera.h"
#include "../toolbox/Maths.h"

void Camera::loadUniforms(Shader* shader) const {
	shader->setUniform3fv("u_CamPosition", m_Position);
	glm::mat4 viewMatrix = Maths::createViewMatrix(this);
	shader->setUniformMat4f("u_ViewMatrix", viewMatrix);
}

void Camera::updateZoom(float d) {
	m_DistanceFromPlayer -= d;
}

void Camera::updatePitch(float d) {
	m_Pitch -= d;
}

void Camera::updateAngle(float d) {
	m_AngleAroundPlayer -= d;
}

void Camera::move() {
	float horizDistanceFromPlayer = m_DistanceFromPlayer * cos(Maths::toRadians(m_Pitch));
	float vertDistanceFromPlayer = m_DistanceFromPlayer * sin(Maths::toRadians(m_Pitch));

	float theta = m_Player->getRotation().y + m_AngleAroundPlayer;
	float offsetX = horizDistanceFromPlayer * sin(Maths::toRadians(theta));
	float offsetZ = horizDistanceFromPlayer * cos(Maths::toRadians(theta));

	glm::vec3 newPosition(m_Player->getPosition().x - offsetX, m_Player->getPosition().y + vertDistanceFromPlayer, m_Player->getPosition().z - offsetZ);
	setPosition(newPosition);

	m_Yaw = 180 - theta;
}
