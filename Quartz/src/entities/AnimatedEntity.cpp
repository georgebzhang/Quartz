#include "AnimatedEntity.h"
#include "../renderEngine/OBJLoader.h"

AnimatedEntity::AnimatedEntity(Loader* loader, int numFrames, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : m_Loader(loader), m_Position(position), m_Rotation(rotation), m_Scale(scale) {
	std::string folderPath = "res/models/animations/";
	Texture* texture = new Texture("res/textures/white.png");
	for (int i = 0; i < numFrames; ++i) {
		std::string fileName = "sphere1_";
		fileName += std::to_string(i) + ".obj";
		//std::cout << folderPath + fileName << std::endl;
		RawModel* rawModel = OBJLoader::loadOBJModel(folderPath + fileName, loader);
		TexturedModel* texturedModel = new TexturedModel(rawModel, texture);
		m_Entities.emplace_back(new Entity(texturedModel, m_Position, m_Rotation, m_Scale));
	}
	m_Entity = m_Entities[0];
}

AnimatedEntity::~AnimatedEntity() {
}

void AnimatedEntity::nextFrame() {
	if (m_IsAnimating) {
		if (m_CurrentFrame == m_Entities.size()-1) {
			m_Entity = m_Entities[m_CurrentFrame];
			m_CurrentFrame = 0;
			//m_IsAnimating = false;
		} else {
			m_Entity = m_Entities[m_CurrentFrame];
			m_CurrentFrame++;
		}
	}
}
