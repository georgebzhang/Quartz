#pragma once

#include "glm/glm.hpp"

class Camera {
public:
	inline glm::vec3 getPosition() const { return m_Position; }
	inline float getPitch() const { return m_Pitch; }
	inline float getYaw() const { return m_Yaw; }
	inline float getRoll() const { return m_Roll; }

	void translate(const glm::vec3 translation);

private:
	glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_Pitch, m_Yaw, m_Roll;
};