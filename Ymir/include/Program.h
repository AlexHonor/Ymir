#pragma once
#include "Shader.h"
#include "glm\glm.hpp"
#include <GL/glew.h>

#include <unordered_map>
#include <string>

using std::unordered_map;
using std::string;

class Program {
public:
    Program();
	Program(const unordered_map<GLenum, string> &src);

	void Use() const;

    bool BuildFromSource(const unordered_map<GLenum, string> &src);
    
    bool TrySetUniform(string name, glm::mat4x4 mat) const;
    bool TrySetUniform(string name, glm::mat3x3 mat) const;
    bool TrySetUniform(string name, GLuint mat) const;
    
    bool IsValid() const;

	~Program();

protected:
    void BindAttributeLocations();
    
    void Attach(const Shader &prog) const;
	void Detach(const Shader &prog) const;

	string name;

	GLuint res;
};