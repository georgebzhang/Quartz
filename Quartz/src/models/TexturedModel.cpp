#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel& model, Texture& texture) : m_RawModel(model), m_Texture(texture) {
}

RawModel TexturedModel::getRawModel() {
	return m_RawModel;
}

Texture TexturedModel::getTexture() {
	return m_Texture;
}

TexturedModel::~TexturedModel() {

}
