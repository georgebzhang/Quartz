#include "RawModel.h"

RawModel::RawModel(int vaoID, int vertexCount) {
	m_VAOID = vaoID;
	m_VertexCount = vertexCount;
}

int RawModel::getVAOID() {
	return m_VAOID;
}

int RawModel::getVertexCount() {
	return m_VertexCount;
}

RawModel::~RawModel() {
}
