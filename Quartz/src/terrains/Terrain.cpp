#include "Terrain.h"

const float Terrain::SIZE = 800;

Terrain::Terrain(int x, int z, Loader* loader, Texture* texture) {
	int vertex_count = VERTEX_SIDE_COUNT * VERTEX_SIDE_COUNT;

}

Terrain::~Terrain() {
	delete m_RawModel;
	delete m_Texture;
}

RawModel* Terrain::loadTerrain(Loader* loader) {
	return nullptr;
}
