#include "TexturedModel.h"

RawModel* TexturedModel::getRawModel() const {
	return m_RawModel;
}

Texture* TexturedModel::getTexture() const {
	return m_Texture;
}

TexturedModel::~TexturedModel() {
	delete m_RawModel;
	delete m_Texture;
}
