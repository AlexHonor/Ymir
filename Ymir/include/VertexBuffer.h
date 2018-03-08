/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include <GL/glew.h>

// Basic VBO class just generation and binding

class VertexBuffer {
 public:
 	// size = number of bytes
 	VertexBuffer(const void* data, unsigned int size);
 	~VertexBuffer();
 	void Bind() const;
 	void Unbind() const;
 private:
	unsigned int vboID;
};