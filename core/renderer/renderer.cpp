#include "renderer.h"

Renderer::Renderer(Rspec specs) {

    i32 unit_size = 0;
    i32 stride = 0;
    i32 count = 0;

    this->vertices_count = 0;
    this->spec = specs;
    this->max_vertex_buffer_size = specs.max_vertices;
    this->vertex_buffer_index = 0;

    this->render_shader = Shader(this->spec.shader_src.vertex_shader, this->spec.shader_src.fragment_shader);
    this->render_shader.compile();
    
    glc(glGenVertexArrays(1, &this->vao));
    glc(glBindVertexArray(this->vao));

    glc(glGenBuffers(1, &this->vb));
    glc(glBindBuffer(GL_ARRAY_BUFFER, this->vb));
    
    // Calculating unit vertex size
    for (auto i = specs.format.begin(); i != specs.format.end(); ++i) {
        unit_size += sizeof(i->type) * i->count;
        this->vertices_count += i->count;
    }

    this->vertex_buffer = (float*) malloc(specs.max_vertices * unit_size);

    glc(glBufferData(GL_ARRAY_BUFFER, specs.max_vertices * unit_size, NULL, GL_DYNAMIC_DRAW));
    
    // Calculating stride
    for (auto i = specs.format.begin(); i != specs.format.end(); ++i) {
       glc(glEnableVertexAttribArray(count));
       glc(glVertexAttribPointer(count, i->count, i->type, GL_FALSE, unit_size, (const void*) stride));
       stride += sizeof(i->type) * i->count;
       count += 1;
    }

    glc(glBindVertexArray(0));
    glc(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void Renderer::begin() {

    this->vertex_buffer_index = 0;
    glc(glClear(GL_COLOR_BUFFER_BIT));
    glc(glClearColor(0.46f, 0.46f, 0.46f, 1.0f));
    glc(glBindBuffer(GL_ARRAY_BUFFER, this->vb));
    glc(glBindVertexArray(this->vao));
    this->render_shader.bind();
}

void Renderer::end() {

    glc(glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertex_buffer_index * sizeof(f32), this->vertex_buffer));

    u32 vertex_count = this->vertex_buffer_index / this->vertices_count;

    glc(glDrawArrays(GL_TRIANGLES, 0, vertex_count));
}

void Renderer::push_vertices(Vertices& vertices) {

    for (auto i = vertices.begin(); i != vertices.end(); ++i) {
        if(this->vertex_buffer_index / this->vertices_count >= this->max_vertex_buffer_size) {
            this->end();
            this->begin();
        }

        this->vertex_buffer[this->vertex_buffer_index] = *i;
        this->vertex_buffer_index += 1;
    } 
}

