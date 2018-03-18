/*
	Copyright 2018 /2 /1 & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include <GL/glew.h>
#include <vector>
#include <cassert>
#include <iostream>

#include <Attribute.h>


class Layout {
 public:
	 Layout() : stride(0) {}
	void Push(const Attribute& attrib) {
		elements.push_back(attrib);
		stride += attrib.count*Attribute::GetSizeOfType(attrib.type);
	}
 	inline const std::vector<Attribute> GetElements() const { return elements; }
 	inline unsigned int GetStride() const { return stride; }

 private:
	 std::vector<Attribute> elements;
	 unsigned int stride;
};