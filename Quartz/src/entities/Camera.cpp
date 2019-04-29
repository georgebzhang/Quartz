#include "Camera.h"

void Camera::translate(const glm::vec3 translation) {
	m_Position += translation;
}
