#pragma once

#include "../models/RawModel.h"
#include "../textures/Texture.h"
#include "../renderEngine/Loader.h"
#include "../textures/TexturePack.h"

class Terrain {
public:
	Terrain(int x, int z, Loader* loader, TexturePack* texturePack, Texture* blendMap);
	~Terrain();

	inline float getX() const { return m_X; }
	inline float getZ() const { return m_Z; }
	inline glm::vec3 getPosition() const { return m_Position; }
	inline RawModel* getRawModel() const { return m_RawModel; }
	inline TexturePack* getTexturePack() const { return m_TexturePack; }
	inline Texture* getBlendMap() const { return m_BlendMap; }

private:
	static const float SIZE;
	static const int VERTEX_SIDE_COUNT = 128;

	float m_X, m_Z;
	glm::vec3 m_Position;
	RawModel* m_RawModel;
	TexturePack* m_TexturePack;
	Texture* m_BlendMap;

	RawModel* loadTerrain(Loader* loader);
};