#pragma once

#include "Entity.h"
#include "../renderEngine/Loader.h"

class LerpEntity {
public:
	LerpEntity(Loader* loader, const std::string& filePath1, const std::string& filePath2, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	~LerpEntity();

	void lerp();

	inline Entity* getEntity() const { return m_Entity; }

private:
	Loader* m_Loader;
	Entity* m_Entity;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	float* m_Positions1;
	float* m_Positions2;
	int mCount;
	int numSteps = 10;
};