/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#include "VertexArrayBuffer.h"


VertexArray::VertexArray(): freeAttribNumber(0) {
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
	const std::vector<VB_Element> elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		VB_Element element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, 
							  element.normalized, layout.GetStride(),
							  (const void *) offset);
		offset = element.count * VB_Element::GetSizeOfType(element.type);
	}
	freeAttribNumber += static_cast<unsigned int>(elements.size());
}