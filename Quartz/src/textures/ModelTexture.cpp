#include "ModelTexture.h"

ModelTexture::ModelTexture(int id) {
	this->textureID = id;
}

int ModelTexture::getID() {
	return this->textureID;
}
