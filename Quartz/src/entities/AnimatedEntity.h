#pragma once

#include "../models/TexturedModel.h"
#include "../renderEngine/Loader.h"
#include "Entity.h"

class AnimatedEntity {
public:
	AnimatedEntity(Loader* loader, int numFrames, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
	~AnimatedEntity();

	inline bool getIsAnimating() const { return m_IsAnimating; }
	inline void setIsAnimating(bool isAnimating) { m_IsAnimating = isAnimating; }

	void nextFrame();

	inline Entity* getEntity() const { return m_Entity; }

	inline glm::vec3 getPosition() const { return m_Position; }
	inline glm::vec3 getRotation() const { return m_Rotation; }
	inline glm::vec3 getScale() const { return m_Scale; }

	inline void setPosition(const glm::vec3& position) { m_Position = position; }
	inline void setPositionY(float y) { m_Position.y = y; }
	inline void setRotation(const glm::vec3& rotation) { m_Rotation = rotation; }
	inline void setScale(const glm::vec3& scale) { m_Scale = scale; }

	inline void translate(const glm::vec3& translation) { m_Position += translation; }
	inline void rotate(const glm::vec3& rotation) { m_Rotation += rotation; }

private:
	Loader* m_Loader;
	//std::vector<TexturedModel*> m_TexturedModels;
	std::vector<Entity*> m_Entities;
	//TexturedModel* m_TexturedModel;
	Entity* m_Entity;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	bool m_IsAnimating = false;
	int m_CurrentFrame = 0;
};