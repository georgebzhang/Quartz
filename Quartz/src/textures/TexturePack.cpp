#include "TexturePack.h"

TexturePack::~TexturePack() {
	delete m_BackgroundTexture;
	delete m_RTexture;
	delete m_GTexture;
	delete m_BTexture;
}
