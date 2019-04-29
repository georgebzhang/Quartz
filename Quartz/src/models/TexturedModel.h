#pragma once

#include "RawModel.h"
//#include "../textures/ModelTexture.h"
#include "../textures/Texture.h"

class TexturedModel {
public:
	TexturedModel(RawModel& model, Texture& texture);
	RawModel getRawModel();
	Texture getTexture();
	~TexturedModel();

private:
	RawModel& m_RawModel;
	Texture& m_Texture;
};