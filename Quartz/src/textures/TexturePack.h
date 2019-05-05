#pragma once

#include "Texture.h"

class TexturePack {
public:
	TexturePack(Texture* backgroundTexture, Texture* rTexture, Texture* gTexture, Texture* bTexture) : m_BackgroundTexture(backgroundTexture), m_RTexture(rTexture), m_GTexture(gTexture), m_BTexture(bTexture) {}
	~TexturePack();

	inline Texture* getBackgroundTexture() const { return m_BackgroundTexture; }
	inline Texture* getRTexture() const { return m_RTexture; }
	inline Texture* getGTexture() const { return m_GTexture; }
	inline Texture* getBTexture() const { return m_BTexture; }

private:
	Texture* m_BackgroundTexture, * m_RTexture, * m_GTexture, * m_BTexture;
};