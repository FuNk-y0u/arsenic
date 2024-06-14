#include "arsenic.h"
#include "error/error.h"

void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader){
    bind_shader(shader);
    bind_index_buffer(ib);
	bind_vertex_array(va);
    glDrawElements(GL_TRIANGLES, ib->count, GL_UNSIGNED_INT, NULL);
}

void clear(){
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void exit_arsenic(const VertexBuffer* vb,const VertexArray* va, const IndexBuffer* ib, const Shader* shader, const Window* window){
    free_index_buffer(ib);
	free_vertex_buffer(vb);
	free_vertex_array(va);
	free_shader(shader);
	free_window(window);
}