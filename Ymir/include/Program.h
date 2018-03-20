#pragma once
#include <Shader.h>
#include <glm\glm.hpp>
#include <GL/glew.h>

#include <unordered_map>
#include <string>
#include <sstream>

#include <RegisterAttrib.h>

using std::unordered_map;
using std::string;
using std::stringstream;

class Program {
public:
    Program();
	Program(const unordered_map<GLenum, string> &src);

	void Use() const;

    bool BuildFromSource(const unordered_map<GLenum, string> &src);
    
    bool SetUniform(const string &name, const glm::mat4x4 &mat) const;
    bool SetUniform(string name, glm::mat3x3 mat) const;
    bool SetUniform(string name, GLuint mat) const;
    
    string DebugListUniforms() const;

    bool IsValid() const;

	~Program();

protected:
    void BindAttributeLocations();
    
    bool BuildUniformTable();

    void Attach(const Shader &prog) const;
	void Detach(const Shader &prog) const;

    struct Uniform {
        GLenum type;
        GLint size;
        GLuint slot;
    };

    unordered_map<string, Uniform> uniforms;

	string name;

	GLuint res;
};