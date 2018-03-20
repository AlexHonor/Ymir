#include <Program.h>

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

    BuildUniformTable();

    for (auto &shader : shaders) {
        Detach(shader.second);
    }

	return true;
}

void Program::BindAttributeLocations() {
    auto &attribTable = RegisterAttrib::AttribTypeTable().GetTable();

    for (auto &attrib : attribTable) {
        glBindAttribLocation(res, attrib.second.slot, attrib.first.c_str());
    }
}

bool Program::SetUniform(const string &name, const glm::mat4x4 &mat) const {
    auto uniform = uniforms.find(name);
    
    if (uniform != uniforms.end()) {
        Use(); 
        glUniformMatrix4fv(uniform->second.slot, 1, GL_FALSE, &mat[0][0]);
        return true;
    } else {
        return false;
    }
}

bool Program::SetUniform(string name, glm::mat3x3 mat) const {
    GLuint location = glGetUniformLocation(res, name.c_str()); 
    
    if (location != -1) {
        Use(); 
        glUniformMatrix3fv(location, 1, GL_FALSE, &mat[0][0]);
        return true;
    } else {
        return false;
    }
}

bool Program::SetUniform(string name, GLuint val) const {
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

bool Program::BuildUniformTable() {
    GLint count;
    glGetProgramiv(res, GL_ACTIVE_UNIFORMS, &count);
    
    for (int id = 0; id < count; id++) {
        const size_t BUF_SIZE = 256;
        char name[BUF_SIZE];
        
        GLenum type;
        GLsizei size = 0;
        GLsizei length = 0;
        glGetActiveUniform(res, id, BUF_SIZE, &length, &size, &type, name);

        uniforms[name].size = size;
        uniforms[name].type = type;
        uniforms[name].slot = glGetUniformLocation(res, name);
    }
    return true;
}

string Program::DebugListUniforms() const {
    stringstream ss;
    ss << "[";
    for (auto &uniform : uniforms) {
        ss << " { Name: " << uniform.first;
        ss << " Type: " << uniform.second.type;
        ss << " Slot: " << uniform.second.slot;
        ss << " Size: " << uniform.second.size << " }";
    }
    ss << "]";
    return ss.str();
}

void Program::Attach(const Shader &shader) const {
	glAttachShader(res, shader.res); 
}
void Program::Detach(const Shader &shader) const {
	glDetachShader(res, shader.res); 
}

Program::~Program() {
    glDeleteProgram(res);
}