/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#include <RegisterAttrib.h>
#include <iostream>

using std::pair;
using std::string;
using std::cout;
using std::endl;

void RegisterAttrib::AddAttribute(string name, GLuint type, unsigned int count,
							   unsigned char normalized, GLuint slot) {
	table.insert(pair<string, Attribute>(name, { type, count, normalized, name, slot }));
}

const Attribute RegisterAttrib::GetAttribute(std::string name){
	std::unordered_map<string, Attribute>::iterator it = table.find(name);
	if (it != table.end()) {
		return it->second;
	}
	cout << " No AttributeType " << name << " was found. " << endl;
	return Attribute();
}

const std::unordered_map <std::string, Attribute> RegisterAttrib::GetTable() const {
    return table;
}