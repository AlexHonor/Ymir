/*
	Copyright 2018 /2 /1 & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once

#include <GL/glew.h>
#include <cassert>
#include <string>

struct Attribute {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
	std::string name;
	GLuint slot;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: 			return sizeof(GLfloat);
			case GL_UNSIGNED_INT: 	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
		}
		assert(false);
		return 0;
	}
};