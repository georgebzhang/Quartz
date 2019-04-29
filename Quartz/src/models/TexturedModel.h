#pragma once

#include "RawModel.h"
#include "../textures/Texture.h"

class TexturedModel {
public:
	TexturedModel(RawModel* rawModel, Texture* texture) : m_RawModel(rawModel), m_Texture(texture) {}
	RawModel* getRawModel() const;
	Texture* getTexture() const;
	~TexturedModel();

private:
	RawModel* m_RawModel;
	Texture* m_Texture;
};