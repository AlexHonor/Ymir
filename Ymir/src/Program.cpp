#include "Program.h"

Program::Program() {}

Program::Program(const unordered_map<GLenum, string> &src) {
    if (!BuildFromSource(src)) {
        // Report error
    }
}

void Program::Use() const {
    glUseProgram(res);
}

bool Program::BuildFromSource(const unordered_map<GLenum, string> &src) {
    unordered_map<GLenum, Shader> shaders;

    for (auto &shaderStage : src) {
        shaders[shaderStage.first].Compile(shaderStage.second, shaderStage.first);
    }

    res = glCreateProgram();

    for (auto &shader : shaders) {
        Attach(shader.second);
    }

    BindAttributeLocations();
    glBindFragDataLocation(res, 0, "out_color");

    glLinkProgram(res);

    GLint is_linked = 0;
    glGetProgramiv(res, GL_LINK_STATUS, &is_linked);

    if (!is_linked) {
        GLint max_length = 0;
        glGetProgramiv(res, GL_INFO_LOG_LENGTH, &max_length);

        max_length++;
        std::vector<GLchar> info_log(max_length);
        *info_log.rbegin() = '\0';

        glGetProgramInfoLog(res, max_length, &max_length, info_log.data());

        glDeleteProgram(res);

        SDL_Log(info_log.data());

        // Report errors
    }

    for (auto &shader : shaders) {
        Detach(shader.second);
    }

	return true;
}

void Program::BindAttributeLocations() {
//    glBindAttribLocation(res, VertexAttribute::POSITION , "a_position" ); 
}

bool Program::TrySetUniform(string name, glm::mat4x4 mat) const {
    GLuint location = glGetUniformLocation(res, name.c_str()); 
    
    if (location != -1) {
        Use(); 
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
        return true;
    } else {
        return false;
    }
}

bool Program::TrySetUniform(string name, glm::mat3x3 mat) const {
    GLuint location = glGetUniformLocation(res, name.c_str()); 
    
    if (location != -1) {
        Use(); 
        glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
        return true;
    } else {
        return false;
    }
}

bool Program::TrySetUniform(string name, GLuint val) const {
    GLuint location = glGetUniformLocation(res, name.c_str()); 
    
    if (location != -1) {
        Use(); 
        glUniform1i(location, val); 
        return true;
    } else {
        return false;
    }
}

bool Program::IsValid() const {
    bool is_valid = glIsProgram(res); 
    return is_valid;
}

void Program::Attach(const Shader &shader) const {
	glAttachShader(res, shader.res); 
}
void Program::Detach(const Shader &shader) const {
	glDetachShader(res, shader.res); 
}

Program::~Program() {
	
}