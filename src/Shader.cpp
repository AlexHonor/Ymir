/*
	Copyright 2018 Gorbonosov Alexey & Borzov Sergey
	Contact: berserk323@yandex.ru
*/

#include "Shader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::unordered_map<GLenum, std::string> &inputShaders) {

  shader = glCreateProgram();

  if (inputShaders.find(GL_VERTEX_SHADER) != inputShaders.end()) {
    shaderObjects[GL_VERTEX_SHADER] = LoadShaderObject(GL_VERTEX_SHADER, inputShaders.at(GL_VERTEX_SHADER));
    glAttachShader(shader, shaderObjects[GL_VERTEX_SHADER]);
  }

  if (inputShaders.find(GL_FRAGMENT_SHADER) != inputShaders.end()) {
    shaderObjects[GL_FRAGMENT_SHADER] = LoadShaderObject(GL_FRAGMENT_SHADER, inputShaders.at(GL_FRAGMENT_SHADER));
    glAttachShader(shader, shaderObjects[GL_FRAGMENT_SHADER]);
  }
  if (inputShaders.find(GL_GEOMETRY_SHADER) != inputShaders.end()) {
    shaderObjects[GL_GEOMETRY_SHADER] = LoadShaderObject(GL_GEOMETRY_SHADER, inputShaders.at(GL_GEOMETRY_SHADER));
    glAttachShader(shader, shaderObjects[GL_GEOMETRY_SHADER]);
  }
  if (inputShaders.find(GL_TESS_CONTROL_SHADER) != inputShaders.end()) {
    shaderObjects[GL_TESS_CONTROL_SHADER] = LoadShaderObject(GL_TESS_CONTROL_SHADER,
      inputShaders.at(GL_TESS_CONTROL_SHADER));
    glAttachShader(shader, shaderObjects[GL_TESS_CONTROL_SHADER]);
  }
  if (inputShaders.find(GL_TESS_EVALUATION_SHADER) != inputShaders.end()) {
    shaderObjects[GL_TESS_EVALUATION_SHADER] = LoadShaderObject(GL_TESS_EVALUATION_SHADER,
      inputShaders.at(GL_TESS_EVALUATION_SHADER));
    glAttachShader(shader, shaderObjects[GL_TESS_EVALUATION_SHADER]);
  }
  if (inputShaders.find(GL_COMPUTE_SHADER) != inputShaders.end()) {
    shaderObjects[GL_COMPUTE_SHADER] = LoadShaderObject(GL_COMPUTE_SHADER, inputShaders.at(GL_COMPUTE_SHADER));
    glAttachShader(shader, shaderObjects[GL_COMPUTE_SHADER]);
  }

  glLinkProgram(shader);

  GLint linkStatus;


  glGetProgramiv(shader, GL_LINK_STATUS, &linkStatus);
  if (linkStatus != GL_TRUE) {
    GLchar infoLog[512];
    glGetProgramInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader program linking failed\n" << infoLog << std::endl;
    shader = 0;
  }

}


void Shader::Release()
{
  if (shaderObjects.find(GL_VERTEX_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_VERTEX_SHADER]);
    glDeleteShader(shaderObjects[GL_VERTEX_SHADER]);
  }

  if (shaderObjects.find(GL_FRAGMENT_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_FRAGMENT_SHADER]);
    glDeleteShader(shaderObjects[GL_FRAGMENT_SHADER]);
  }

  if (shaderObjects.find(GL_GEOMETRY_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_GEOMETRY_SHADER]);
    glDeleteShader(shaderObjects[GL_GEOMETRY_SHADER]);
  }

  if (shaderObjects.find(GL_TESS_CONTROL_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_TESS_CONTROL_SHADER]);
    glDeleteShader(shaderObjects[GL_TESS_CONTROL_SHADER]);
  }

  if (shaderObjects.find(GL_TESS_EVALUATION_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_TESS_EVALUATION_SHADER]);
    glDeleteShader(shaderObjects[GL_TESS_EVALUATION_SHADER]);
  }
  if (shaderObjects.find(GL_COMPUTE_SHADER) != shaderObjects.end()) {
    glDetachShader(shader, shaderObjects[GL_COMPUTE_SHADER]);
    glDeleteShader(shaderObjects[GL_COMPUTE_SHADER]);
  }

  glDeleteProgram(shader);
}

bool Shader::ReLink()
{
  GLint linked;

  glLinkProgram(shader);
  glGetProgramiv(shader, GL_LINK_STATUS, &linked);

  if (!linked) {
    GLint logLength, charsWritten;
    glGetProgramiv(this->shader, GL_INFO_LOG_LENGTH, &logLength);

    auto log = new char[logLength];
    glGetProgramInfoLog(this->shader, logLength, &charsWritten, log);

    std::cerr << "Shader program link error: " << std::endl << log << std::endl;

    delete[] log;
    shader = 0;
    return false;
  }

  return true;
}


GLuint Shader::LoadShaderObject(GLenum type, const std::string &filename) {
  std::ifstream fs(filename);

  if (!fs.is_open()) {
    std::cerr << "ERROR: Could not read shader from " << filename << std::endl;
    return 0;
  }

  std::string shaderText((std::istreambuf_iterator<char>(fs)), std::istreambuf_iterator<char>());

  GLuint newShaderObject = glCreateShader(type);

  const char *shaderSrc = shaderText.c_str();
  glShaderSource(newShaderObject, 1, &shaderSrc, nullptr);

  glCompileShader(newShaderObject);

  GLint compileStatus;
  glGetShaderiv(newShaderObject, GL_COMPILE_STATUS, &compileStatus);

  if (compileStatus != GL_TRUE) {
    GLchar infoLog[512];
    glGetShaderInfoLog(newShaderObject, 512, nullptr, infoLog);
    std::cerr << "Shader compilation failed : " << std::endl << infoLog << std::endl;
    return 0;
  }

  return newShaderObject;
}

void Shader::RunShader() const {
  glUseProgram(shader);
}

void Shader::StopShader() const {
  glUseProgram(0);
}

void Shader::SetUniform(const std::string &location, const glm::mat4 &value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }

  glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string &location, int value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1i(uniformLocation, value);
}

void Shader::SetUniform(const std::string &location, unsigned int value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1ui(uniformLocation, value);
}

void Shader::SetUniform(const std::string &location, float value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1f(uniformLocation, value);
}

void Shader::SetUniform(const std::string &location, double value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  glUniform1d(uniformLocation, value);
}

void Shader::SetUniform(const std::string &location, const glm::vec4 &value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1)
  {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y, value.z, value.w };
  glUniform4fv(uniformLocation, 1, val);
}

void Shader::SetUniform(const std::string &location, const glm::vec3 &value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y, value.z };
  glUniform3fv(uniformLocation, 1, val);
}

void Shader::SetUniform(const std::string &location, const glm::vec2 &value) const {
  GLint uniformLocation = glGetUniformLocation(shader, location.c_str());
  if (uniformLocation == -1) {
    std::cerr << "Uniform  " << location << " not found" << std::endl;
    return;
  }
  float val[] = { value.x, value.y };
  glUniform2fv(uniformLocation, 1, val);
}
