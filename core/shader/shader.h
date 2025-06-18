#pragma once
#include <common.h>

class Shader{
    public:
        u32 id;
        Shader(const char* vertex_shader, const char* fragment_shader);

        void compile_shader();
        void bind();
        void unbind();
    private:
        u32 vs;
        u32 fs;

};

