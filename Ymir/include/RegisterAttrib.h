/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/
#pragma once
#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <Attribute.h>

/* 
	singleton retarded table
*/


class RegisterAttrib {
 public:
	 void AddAttribute(std::string name, GLuint type, unsigned int count,
					unsigned char normalized, GLuint slot);
	 const Attribute GetAttribute(std::string name);
	 static RegisterAttrib& AttribTypeTable() {
		 static RegisterAttrib AttribTypeTable;
		 return AttribTypeTable;
	 }
 private:
	 std::unordered_map <std::string, Attribute> table;
	 RegisterAttrib() {};
	 RegisterAttrib(const RegisterAttrib& root) = delete;
	 RegisterAttrib& operator=(const RegisterAttrib&) = delete;
};