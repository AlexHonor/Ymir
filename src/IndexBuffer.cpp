/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#include "IndexBuffer.h"

// count = number ( not bytes )
IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count): indexCount(count) {
	glGenBuffers(1, &vibID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vibID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &vibID);
}

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vibID);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetCount() const {
	return indexCount;
}