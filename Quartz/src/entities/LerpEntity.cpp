#include "LerpEntity.h"
#include "../renderEngine/OBJLoader.h"

LerpEntity::LerpEntity(Loader* loader, const std::string& filePath1, const std::string& filePath2, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : m_Loader(loader), m_Position(position), m_Rotation(rotation), m_Scale(scale) {
	Buffer* buffer1 = OBJLoader::loadOBJModel2(filePath1, loader);
	Buffer* buffer2 = OBJLoader::loadOBJModel2(filePath2, loader);
	RawModel* rawModel = loader->loadToVAO(buffer1->m_Positions, buffer1->m_Pcount, buffer1->m_TexCoords, buffer1->m_Tcount, buffer1->m_Normals, buffer1->m_Ncount, buffer1->m_Indices, buffer1->m_Icount);
	//RawModel* rawModel = loader->loadToVAO(buffer2->m_Positions, buffer2->m_Pcount, buffer2->m_TexCoords, buffer2->m_Tcount, buffer2->m_Normals, buffer2->m_Ncount, buffer2->m_Indices, buffer2->m_Icount);
	Texture* texture = new Texture("res/textures/white.png");
	TexturedModel* texturedModel = new TexturedModel(rawModel, texture);
	m_Entity = new Entity(texturedModel, m_Position, m_Rotation, m_Scale);
}

LerpEntity::~LerpEntity() {

}

void LerpEntity::lerp() {

}
