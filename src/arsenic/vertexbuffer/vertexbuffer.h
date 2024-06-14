#include "globalheader.h"

typedef struct {
    unsigned int id;
} VertexBuffer;

VertexBuffer* create_vertex_buffer(const void* data, unsigned int size);
void bind_vertex_buffer(VertexBuffer* vertexBuffer);
void unbind_vertex_buffer();
void free_vertex_buffer(VertexBuffer* vertexBuffer);