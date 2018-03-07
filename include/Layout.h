/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include <GL/glew.h>
#include <vector>
#include <cassert>
#include <iostream>

// Structure describing bytes in VBO
// Here everything for glVertexAttribPointer stored

struct VB_Element {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(int type) {
		switch(type) {
			case GL_FLOAT: 			return sizeof(GLfloat);
			case GL_UNSIGNED_INT: 	return sizeof(GLuint);
			case GL_UNSIGNED_BYTE:  return sizeof(GLubyte);
		}
		assert(false);
		return 0;
	}
};

// Layout consists of VB_Elements so you can use single array
// for a lot of attributes
// This thing describes what bytes are stored in a VBO

class Layout {
	std::vector<VB_Element> elements;
	unsigned int stride;
 public:
	 Layout() : stride(0) {}

	/* Most interesting part. Here template specification is used
	   so you can get attribute from any kind of shit */

 	template<typename T>
 	void Push(unsigned int count) {

		/* Shit happened.
			TODO: Add some kind of error message etc.
		*/
 		static_assert(false);
 	}

	template<>
	void Push<float>(unsigned int count) {
 		elements.push_back({GL_FLOAT, count, GL_FALSE});
		stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
 		elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
		stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
 		elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
		stride += count * sizeof(GLubyte);
	}

	/* Any new type can be added theoretically, but it's type number have to differ from GL constants */

	/*	template<>
	    void Push<glm::vec3>(unsigned int cout) {
			elements.push_back({777, count, false});
			stride += count * sizeof(glm::vec3);
		}
	*/
 	
 	inline const std::vector<VB_Element> GetElements() const { return elements; }
 	inline unsigned int GetStride() const { return stride; }
};