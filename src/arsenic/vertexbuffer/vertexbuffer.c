#include "vertexbuffer.h"
#include "error/error.h"

VertexBuffer* create_vertex_buffer(const void* data, unsigned int size){
    VertexBuffer* vb = (VertexBuffer*)malloc(sizeof(VertexBuffer));
    GLCall(glGenBuffers(1, &vb->id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb->id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    return vb;
}

void bind_vertex_buffer(VertexBuffer* vertexBuffer){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->id));
}

void unbind_vertex_buffer(){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void free_vertex_buffer(VertexBuffer* vertexBuffer){
    GLCall(glDeleteBuffers(1, &vertexBuffer->id));
    free(vertexBuffer);
}