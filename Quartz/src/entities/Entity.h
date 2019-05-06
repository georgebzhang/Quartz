#pragma once

#include "../models/TexturedModel.h"

#include "glm/glm.hpp"

class Entity {
public:
	Entity(TexturedModel* texturedModel, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : m_TexturedModel(texturedModel), m_Position(position), m_Rotation(rotation), m_Scale(scale) {}
	virtual ~Entity();

	inline TexturedModel* getTexturedModel() const { return m_TexturedModel; }
	inline glm::vec3 getPosition() const { return m_Position; }
	inline glm::vec3 getRotation() const { return m_Rotation; }
	inline glm::vec3 getScale() const { return m_Scale; }

	inline void setTexturedModel(TexturedModel* texturedModel) { m_TexturedModel = texturedModel; }
	inline void setPosition(glm::vec3 position) { m_Position = position; }
	inline void setPositionY(float y) { m_Position.y = y; }
	inline void setRotation(glm::vec3 rotation) { m_Rotation = rotation; }
	inline void setScale(glm::vec3 scale) { m_Scale = scale; }

	void translate(const glm::vec3 translation);
	void rotate(const glm::vec3 rotation);

private:
	TexturedModel* m_TexturedModel;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;
};