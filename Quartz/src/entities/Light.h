#pragma once

#include "glm/glm.hpp"

class Light {
public:
	Light(glm::vec3 position, glm::vec3 color) : m_Position(position), m_Color(color) {}
	~Light() {}

	inline glm::vec3 getPosition() const { return m_Position; }
	inline glm::vec3 getColor() const { return m_Color; }
	inline void setPosition(glm::vec3 position) { m_Position = position; }
	inline void setColor(glm::vec3 color) { m_Color = color; }

private:
	glm::vec3 m_Position;
	glm::vec3 m_Color;
};