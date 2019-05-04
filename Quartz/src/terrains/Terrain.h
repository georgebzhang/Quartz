#pragma once

#include "../models/RawModel.h"
#include "../textures/Texture.h"
#include "../renderEngine/Loader.h"

class Terrain {
public:
	Terrain(int x, int z, Loader* loader, Texture* texture);
	~Terrain();

	inline float getX() const { return m_X; }
	inline float getZ() const { return m_Z; }
	inline RawModel* getRawModel() const { return m_RawModel; }
	inline Texture* getTexture() const { return m_Texture; }

private:
	static const float SIZE;
	static const int VERTEX_SIDE_COUNT = 128;

	float m_X, m_Z;
	RawModel* m_RawModel;
	Texture* m_Texture;

	RawModel* loadTerrain(Loader* loader);
};