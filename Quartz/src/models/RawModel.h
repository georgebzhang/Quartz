#pragma once

#include "../objects/VertexArray.h"
#include "../objects/IndexBuffer.h"

class RawModel {
public:
	RawModel(VertexArray* va, IndexBuffer* ib) : m_VA(va), m_IB(ib) {}
	VertexArray* getVA() const;
	IndexBuffer* getIB() const;
	~RawModel();

private:
	VertexArray* m_VA;
	IndexBuffer* m_IB;
};