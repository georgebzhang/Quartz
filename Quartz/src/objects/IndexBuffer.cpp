#include "IndexBuffer.h"

#include "../errors/ErrorHandler.h"

IndexBuffer::IndexBuffer(const unsigned int * data, unsigned int count) : m_Count(count) {
	GLCall(glGenBuffers(1, &m_ID));
	bind();
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	unbind();
}

IndexBuffer::~IndexBuffer() {
	GLCall(glDeleteBuffers(1, &m_ID));
}

void IndexBuffer::bind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
}

void IndexBuffer::unbind() const {
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
