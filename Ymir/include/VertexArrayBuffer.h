/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Layout.h"

class VertexArray {
 public:
	std::vector<Attribute> attributes;
 	VertexArray();
 	~VertexArray();
 	void Bind() const;
 	void Unbind() const;
 	void AddAttributes(const VertexBuffer& vb, const Layout& layout);
 private:
	unsigned int vaoID;
	

};