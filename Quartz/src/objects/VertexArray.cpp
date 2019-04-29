#include "VertexArray.h"

#include "../errors/ErrorHandler.h"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_ID))
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_ID));
}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_ID));
}

void VertexArray::unbind() const {
	GLCall(glBindVertexArray(0));
}

void VertexArray::addBuffer(const VertexBuffer* vb, unsigned int attribute, int count) {
	bind();
	vb->bind();
	GLCall(glVertexAttribPointer(attribute, count, GL_FLOAT, false, 0, (const void*) 0));
	vb->unbind();
	unbind();
}
