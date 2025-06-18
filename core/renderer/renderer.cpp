#include "renderer.h"

Renderer::Renderer(Rspec specs) {

    this->vertices_count = 0;
    this->spec = specs;
    this->max_vertex_buffer_size = specs.max_vertices;
    this->vertex_buffer_index = 0;

    glGenVertexArrays(1, &this->vao);
    glBindVertexArray(this->vao);

    glGenBuffers(1, &this->vb);
    glBindBuffer(GL_ARRAY_BUFFER, this->vb);
    
    i32 unit_size = 0;
    for (auto i = specs.format.begin(); i != specs.format.end(); ++i) {
        unit_size += sizeof(i->type) * i->count;
        this->vertices_count += i->count;
    }

    glBufferData(GL_ARRAY_BUFFER, specs.max_vertices * unit_size, NULL, GL_DYNAMIC_DRAW);
    
    i32 stride = 0;
    i32 count = 0;

    for (auto i = specs.format.begin(); i != specs.format.end(); ++i) {
       glEnableVertexAttribArray(count);
       glVertexAttribPointer(count, i->count, i->type, GL_FALSE, unit_size, (const void*) stride);
       stride += sizeof(i->type) * i->count;
    }

    Shader shader = Shader(this->spec.shader_src.vertex_shader, this->spec.shader_src.fragment_shader);

    shader.compile_shader();

    this->render_shader = shader;

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::begin() {
    this->vertex_buffer_index = 0;
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glBindBuffer(GL_ARRAY_BUFFER, this->vb);
    glBindVertexArray(this->vao);
    this->render_shader.bind();
}

void Renderer::end() {
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->vertex_buffer_index * sizeof(f32), this->vertex_buffer);
    glDrawArrays(GL_TRIANGLES, 0, this->vertex_buffer_index / this->vertices_count);
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

