#include "RawModel.h"

RawModel::RawModel(int vaoID, int vertexCount) {
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

int RawModel::getVAOID() {
	return vaoID;
}

int RawModel::getVertexCount() {
	return vertexCount;
}