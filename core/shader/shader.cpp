#include "shader.h"

Shader::Shader(const char* vertex_shader, const char* fragment_shader){
    u32 program = glCreateProgram();

    u32 vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertex_shader, NULL);

    u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragment_shader, NULL);

    this->id = program;

}

// TODO make get shader result a seperate function
void Shader::compile_shader(){
    u32 fs = this->fs;
    u32 vs = this->vs;

    glCompileShader(fs);
    glCompileShader(vs);
    
    int vs_result, vs_length;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_result);

    if(vs_result == GL_FALSE){
        glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &vs_length);

        char vs_message[vs_length];

        glGetShaderInfoLog(vs, vs_length, &vs_length, vs_message);

        std::cout << "FAILED TO COMPILE VERTEX SHADER" << std::endl;

        std::cout << vs_message << std::endl;

    }

    int fs_result, fs_length;
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_result);

    if(vs_result == GL_FALSE){
        glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &fs_length);

        char fs_message[fs_length];

        glGetShaderInfoLog(fs, fs_length, &fs_length, fs_message);

        std::cout << "FAILED TO COMPILE FRAGMENT SHADER" << std::endl;

        std::cout << fs_message << std::endl;

    }

    glAttachShader(this->id, this->vs);
    glAttachShader(this->id, this->fs);

    glLinkProgram(this->id);
    glValidateProgram(this->id);

    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(0);

}

void Shader::bind(){
    glUseProgram(this->id);
}
void Shader::unbind(){
    glUseProgram(0);
}
