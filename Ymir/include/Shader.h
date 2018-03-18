#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <vector>
#include <fstream>

#include <SDL.h>

using std::string;
using std::vector;

class Program;

class Shader {
public:
	Shader();
	
	Shader(const string &src, GLenum type);

	void Compile(const string &src, GLenum type);

	operator bool() const;

	~Shader();

	friend class Program;
private:
	GLuint res;
};