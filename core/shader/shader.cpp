#include "shader.h"

Shader::Shader(){
}

Shader::Shader(const char* vertex_shader, const char* fragment_shader){
    u32 program = glCreateProgram();

    u32 vs = glc(glCreateShader(GL_VERTEX_SHADER));
    glc(glShaderSource(vs, 1, &vertex_shader, NULL));

    u32 fs = glc(glCreateShader(GL_FRAGMENT_SHADER));
    glc(glShaderSource(fs, 1, &fragment_shader, NULL));

    this->id = program;
    this->fs = fs;
    this->vs = vs;

}

void Shader::check_error(u32 id, ShaderType type) {
    int result, length;
    glc(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    if(result == GL_FALSE) {
        glc(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char message[length];

        glc(glGetShaderInfoLog(id, length, &length, message));
        
        if (type == VERTEX) {
            std::cout << "FAILED TO COMPILE VERTEX SHADER" << std::endl;
            std::cout << message << std::endl;
        }
        else{
            std::cout << "FAILED TO COMPILE FRAGMENT SHADER" << std::endl;
            std::cout << message << std::endl;
        }
    }
}

void Shader::compile(){
    u32 fs = this->fs;
    u32 vs = this->vs;

    glc(glCompileShader(fs));
    glc(glCompileShader(vs));
    
    this->check_error(fs, FRAGMENT);
    this->check_error(vs, VERTEX);

    glc(glAttachShader(this->id, this->vs));
    glc(glAttachShader(this->id, this->fs));

    glc(glLinkProgram(this->id));
    glc(glValidateProgram(this->id));

    glc(glDeleteShader(vs));
    glc(glDeleteShader(fs));

    glc(glUseProgram(0));

}

void Shader::bind(){
    glc(glUseProgram(this->id));
}
void Shader::unbind(){
    glc(glUseProgram(0));
}
