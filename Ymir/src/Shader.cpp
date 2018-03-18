#include "shader.h"

Shader::Shader() {}

Shader::Shader(const string &src, GLenum type) {
	Compile(src, type);
}

void Shader::Compile(const string &src, GLenum type) {
    res = glCreateShader(type);

	const GLchar *source = src.c_str();
	glShaderSource(res, 1, &source, nullptr); 

	glCompileShader(res); 

	GLint is_compiled = 0;
	GLuint prog = res;
	glGetShaderiv(res, GL_COMPILE_STATUS, &is_compiled); 
	
	if (!is_compiled) {
		GLint max_length = 0;
		glGetShaderiv(res, GL_INFO_LOG_LENGTH, &max_length); 

		vector<GLchar> log(max_length + 1);
		glGetShaderInfoLog(res, max_length, &max_length, log.data()); 

		SDL_Log(log.data());
        
        //TODO
        // retport error
	}
}
	
Shader::operator bool() const {
	return true;
}

Shader::~Shader() {
    glDeleteShader(res); 
}