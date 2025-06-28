#pragma once
#include <common.h>
#include <shader/shader.h>
#include <error/error.h>

struct Rformat {
    u32 type;
    i32 count;
};

struct Rshader {
    const char* vertex_shader;
    const char* fragment_shader;
};

struct Rspec{
    std::vector<Rformat> format;
    u32 max_vertices;
    Rshader shader_src;
};

typedef std::vector<f32> Vertices;

class Renderer{
    public:
        // Renderer specifications 
        Rspec spec;

        // Vertex Buffer / Vertex Arrays
        u32 vb;
        u32 vao;
        
        // No of vertices in the array buffer
        u32 vertices_count;
        
        f32* vertex_buffer;

        // Index of index of buffer when writing to the vertex buffer 
        i32 vertex_buffer_index;
        
        i32 max_vertex_buffer_size;
    
    public:
        Shader render_shader;

        Renderer(Rspec specs);
        void push_vertices(Vertices& vertices);
        void begin();
        void end();
};

