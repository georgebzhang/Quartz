#pragma once

#include "../shaders/Shader.h"

#include "glm/glm.hpp"

class Camera {
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f)) : m_Position(position) {}
	~Camera() {}

	inline glm::vec3 getPosition() const { return m_Position; }
	inline float getPitch() const { return m_Pitch; }
	inline float getYaw() const { return m_Yaw; }
	inline float getRoll() const { return m_Roll; }

	void translate(const glm::vec3 translation);

	void loadUniforms(Shader* shader) const;

private:
	glm::vec3 m_Position;
	float m_Pitch, m_Yaw, m_Roll;
};