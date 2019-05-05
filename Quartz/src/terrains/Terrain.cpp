#include "Terrain.h"

const float Terrain::SIZE = 100;

Terrain::Terrain(int x, int z, Loader* loader, TexturePack* texturePack, Texture* blendMap) : m_X(x * SIZE), m_Z(z * SIZE), m_Position(glm::vec3(m_X, 0, m_Z)), m_TexturePack(texturePack), m_BlendMap(blendMap) {
	m_RawModel = loadTerrain(loader);
}

Terrain::~Terrain() {
	delete m_RawModel;
	delete m_TexturePack;
	delete m_BlendMap;
}

RawModel* Terrain::loadTerrain(Loader* loader) {
	int vertex_count = VERTEX_SIDE_COUNT * VERTEX_SIDE_COUNT;
	int p_count = vertex_count * 3;
	int n_count = vertex_count * 3;
	int t_count = vertex_count * 2;
	int i_count = 6 * (VERTEX_SIDE_COUNT - 1) * (VERTEX_SIDE_COUNT - 1);
	float* positions = new float[p_count];
	float* normals = new float[n_count];
	float* texCoords = new float[t_count];
	unsigned int* indices = new unsigned int[i_count];
	int vertexIndex = 0;

	// positions, normals, texCoords
	for (int j = 0; j < VERTEX_SIDE_COUNT; ++j) { // z index
		for (int i = 0; i < VERTEX_SIDE_COUNT; ++i) { // x index
			float x_relative = (float)i / ((float)VERTEX_SIDE_COUNT - 1);
			float z_relative = (float)j / ((float)VERTEX_SIDE_COUNT - 1);
			positions[vertexIndex * 3] = x_relative * SIZE;
			positions[vertexIndex * 3 + 1] = 0;
			positions[vertexIndex * 3 + 2] = z_relative * SIZE;
			normals[vertexIndex * 3] = 0;
			normals[vertexIndex * 3 + 1] = 1;
			normals[vertexIndex * 3 + 2] = 0;
			texCoords[vertexIndex * 2] = x_relative;
			texCoords[vertexIndex * 2 + 1] = z_relative;
			vertexIndex++;
		}
	}

	// indices
	int indexIndex = 0;
	for (int j = 0; j < VERTEX_SIDE_COUNT - 1; ++j) { // z index
		for (int i = 0; i < VERTEX_SIDE_COUNT - 1; ++i) { // x index
			int topLeftIndex = j * VERTEX_SIDE_COUNT + i;
			int topRightIndex = topLeftIndex + 1;
			int bottomLeftIndex = (j + 1) * VERTEX_SIDE_COUNT + i;
			int bottomRightIndex = bottomLeftIndex + 1;
			indices[indexIndex++] = topLeftIndex;
			indices[indexIndex++] = bottomLeftIndex;
			indices[indexIndex++] = topRightIndex;
			indices[indexIndex++] = topRightIndex;
			indices[indexIndex++] = bottomLeftIndex;
			indices[indexIndex++] = bottomRightIndex;
		}
	}

	return loader->loadToVAO(positions, p_count, texCoords, t_count, normals, n_count, indices, i_count);
}
