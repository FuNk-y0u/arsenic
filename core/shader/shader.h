#pragma once
#include <common.h>
#include <error/error.h>

enum ShaderType {
    FRAGMENT,
    VERTEX
};

class Shader{
    public:
        u32 id;
        Shader(const char* vertex_shader, const char* fragment_shader);
        Shader();

        void compile();
        void bind();
        void unbind();
    private:
        void check_error(u32 id, ShaderType type);
        u32 vs;
        u32 fs;

};

