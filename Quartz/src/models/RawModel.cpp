#include "RawModel.h"

#include <iostream>

VertexArray* RawModel::getVA() const {
	return m_VA;
}

IndexBuffer* RawModel::getIB() const {
	return m_IB;
}

RawModel::~RawModel() {
	delete m_VA;
	delete m_IB;
}
