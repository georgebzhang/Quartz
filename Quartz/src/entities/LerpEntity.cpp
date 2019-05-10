#include "LerpEntity.h"

LerpEntity::LerpEntity(Loader* loader, const std::string& filePath1, const std::string& filePath2, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale) : m_Loader(loader), m_FilePath1(filePath1), m_FilePath2(filePath2), m_Position(position), m_Rotation(rotation), m_Scale(scale) {
	m_Buffer1 = OBJLoader::loadOBJModel2(m_FilePath1, m_Loader);
	m_Buffer = OBJLoader::loadOBJModel2(m_FilePath1, m_Loader);
	m_Buffer2 = OBJLoader::loadOBJModel2(m_FilePath2, m_Loader);
	RawModel* rawModel = m_Loader->loadToVAO(m_Buffer1->m_Positions, m_Buffer1->m_Pcount, m_Buffer1->m_TexCoords, m_Buffer1->m_Tcount, m_Buffer1->m_Normals, m_Buffer1->m_Ncount, m_Buffer1->m_Indices, m_Buffer1->m_Icount);
	//RawModel* rawModel = m_Loader->loadToVAO(m_Buffer2->m_Positions, m_Buffer2->m_Pcount, m_Buffer2->m_TexCoords, m_Buffer2->m_Tcount, m_Buffer2->m_Normals, m_Buffer2->m_Ncount, m_Buffer2->m_Indices, m_Buffer2->m_Icount);
	m_TexturedModel = new TexturedModel(rawModel, m_Texture);
	m_Entity = new Entity(m_TexturedModel, m_Position, m_Rotation, m_Scale);

	int pcount = m_Buffer1->m_Pcount;
	int ncount = m_Buffer1->m_Ncount;

	m_dPositions = new float[pcount];
	m_dNormals = new float[ncount];

	for (int i = 0; i < pcount; ++i) {
		m_dPositions[i] = m_Buffer2->m_Positions[i] - m_Buffer1->m_Positions[i];
	}

	for (int i = 0; i < ncount; ++i) {
		m_dNormals[i] = m_Buffer2->m_Normals[i] - m_Buffer1->m_Normals[i];
	}
}

LerpEntity::~LerpEntity() {

}

void LerpEntity::lerp() {
	if (m_CurrStep == m_NumSteps) {
		//m_Buffer = OBJLoader::loadOBJModel2("res/models/spherelerp.obj", m_Loader);
		m_Buffer = OBJLoader::loadOBJModel2(m_FilePath1, m_Loader);
		RawModel* rawModel = m_Loader->loadToVAO(m_Buffer->m_Positions, m_Buffer->m_Pcount, m_Buffer->m_TexCoords, m_Buffer->m_Tcount, m_Buffer->m_Normals, m_Buffer->m_Ncount, m_Buffer->m_Indices, m_Buffer->m_Icount);
		m_TexturedModel->setRawModel(rawModel);
		//m_Entity = new Entity(m_TexturedModel, m_Position, m_Rotation, m_Scale);
		//delete m_Buffer;
		m_CurrStep = 1;
		done = true;
		return;
	}

	int pcount = m_Buffer1->m_Pcount;
	int ncount = m_Buffer1->m_Ncount;

	for (int i = 0; i < pcount; ++i) {
		m_Buffer->m_Positions[i] += m_dPositions[i] / m_NumSteps;
	}

	for (int i = 0; i < ncount; ++i) {
		//std::cout << m_Buffer->m_Normals[i] << std::endl;
		//std::cout << m_dNormals[i] << std::endl;
		m_Buffer->m_Normals[i] += m_dNormals[i] / m_NumSteps;
	}

	RawModel* rawModel = m_Loader->loadToVAO(m_Buffer->m_Positions, m_Buffer->m_Pcount, m_Buffer->m_TexCoords, m_Buffer->m_Tcount, m_Buffer->m_Normals, m_Buffer->m_Ncount, m_Buffer->m_Indices, m_Buffer->m_Icount);
	m_TexturedModel->setRawModel(rawModel);

	m_CurrStep++;
}
