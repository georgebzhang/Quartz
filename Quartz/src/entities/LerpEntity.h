#pragma once

#include "Entity.h"
#include "../renderEngine/Loader.h"
#include "../renderEngine/OBJLoader.h"

class LerpEntity {
public:
	LerpEntity(Loader* loader, const std::string& filePath1, const std::string& filePath2, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale);
	~LerpEntity();

	void lerp();

	inline Entity* getEntity() const { return m_Entity; }

	bool done = false;

private:
	std::string m_FilePath1;
	std::string m_FilePath2;

	Loader* m_Loader;

	Buffer* m_Buffer1, *m_Buffer2, *m_Buffer;

	float* m_dPositions;
	float* m_dNormals;

	Texture* m_Texture = new Texture("res/textures/white.png");
	TexturedModel* m_TexturedModel;

	Entity* m_Entity;
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	int m_NumSteps = 25;
	int m_CurrStep = 1;
};