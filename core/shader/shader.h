#pragma once
#include <common.h>
#include <error/error.h>

class Shader{
    public:
        u32 id;
        Shader(const char* vertex_shader, const char* fragment_shader);
        Shader();

        void compile_shader();
        void bind();
        void unbind();
    private:
        u32 vs;
        u32 fs;

};

