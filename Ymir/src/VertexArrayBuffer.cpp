/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#include "VertexArrayBuffer.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &vaoID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &vaoID);
}

void VertexArray::Bind() const {
	glBindVertexArray(vaoID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
// Using Layout creating Attributes in a loop
/* TODO: Briefly: Debug
   Check if there are any free slots in a vao for a new attribute
*/

void VertexArray::AddAttributes(const VertexBuffer& vb, const Layout& layout) {
	Bind();
	vb.Bind();
	attributes = layout.GetElements();
	unsigned int offset = 0;
	
	for (auto it = attributes.begin(); it != attributes.end(); it++) {
		glEnableVertexAttribArray(it->slot);
		glVertexAttribPointer(it->slot, it->count, it->type,
							  it->normalized, layout.GetStride(),
							  (const void *) offset);
		offset = it->count * Attribute::GetSizeOfType(it->type);
	}
}