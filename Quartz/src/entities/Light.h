#pragma once

#include "../shaders/Shader.h"

#include "glm/glm.hpp"

class Light {
public:
	Light(const glm::vec3& intensity, const glm::vec3& position, const glm::vec3& color) : m_Intensity(intensity), m_Position(position), m_Color(color) {}
	~Light() {}

	inline glm::vec3 getPosition() const { return m_Position; }
	inline glm::vec3 getColor() const { return m_Color; }
	inline void setPosition(const glm::vec3& position) { m_Position = position; }
	inline void setColor(const glm::vec3& color) { m_Color = color; }

	void loadUniforms(Shader* shader) const;

private:
	glm::vec3 m_Intensity;
	glm::vec3 m_Position;
	glm::vec3 m_Color;
};