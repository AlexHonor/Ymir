/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include <GL/glew.h>

// Same as VertexBuffer
class IndexBuffer {
	unsigned int vibID;
	unsigned int indexCount;
 public:
 	// count = number ( not bytes )
 	IndexBuffer(const unsigned int* data,unsigned int count);
 	~IndexBuffer();
 	void Bind() const;
 	void Unbind() const;
 	unsigned int GetCount() const;
};