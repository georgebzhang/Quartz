#pragma once

#include "VertexBuffer.h"

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void bind() const;
	void unbind() const;
	void addBuffer(const VertexBuffer* vb, unsigned int attribute, int count);

private:
	unsigned int m_ID;
};