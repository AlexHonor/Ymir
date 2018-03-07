/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <unordered_map>
#include <string>

class Shader {
 public:
	 Shader() : shader(-1) {};
	 Shader(const std::unordered_map<GLenum, std::string> &inputShaders);
	 void Release();
	 virtual void RunShader() const;
	 virtual void StopShader() const;
	 GLuint GetProgram() const { return shader; }
	 bool ReLink();
	 void SetUniform(const std::string &location, const glm::mat4 & value) const;
	 void SetUniform(const std::string &location, float value) const;
	 void SetUniform(const std::string &location, double value) const;
	 void SetUniform(const std::string &location, int value) const;
	 void SetUniform(const std::string &loaction, unsigned int value) const;
	 void SetUniform(const std::string &location, const glm::vec4 &value) const;
	 void SetUniform(const std::string &location, const glm::vec3 &value) const;
	 void SetUniform(const std::string &location, const glm::vec2 &value) const;
private:
	 static GLuint LoadShaderObject(GLenum type, const std::string &filename);
	 GLuint shader;
	 std::unordered_map<GLenum, GLuint> shaderObjects;
};