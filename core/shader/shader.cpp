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

// TODO make get shader result a seperate function
void Shader::compile_shader(){
    u32 fs = this->fs;
    u32 vs = this->vs;

    glc(glCompileShader(fs));
    glc(glCompileShader(vs));
    
    int vs_result, vs_length;
    glc(glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_result));

    if(vs_result == GL_FALSE){
        glc(glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &vs_length));

        char vs_message[vs_length];

        glc(glGetShaderInfoLog(vs, vs_length, &vs_length, vs_message));

        std::cout << "FAILED TO COMPILE VERTEX SHADER" << std::endl;

        std::cout << vs_message << std::endl;

    }

    int fs_result, fs_length;
    glc(glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_result));

    if(vs_result == GL_FALSE){
        glc(glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &fs_length));

        char fs_message[fs_length];

        glc(glGetShaderInfoLog(fs, fs_length, &fs_length, fs_message));

        std::cout << "FAILED TO COMPILE FRAGMENT SHADER" << std::endl;

        std::cout << fs_message << std::endl;

    }

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
