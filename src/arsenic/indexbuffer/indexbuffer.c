#include "indexbuffer.h"
#include "error/error.h"


IndexBuffer* create_index_buffer(unsigned int* data, unsigned int count){
    IndexBuffer* ib = (IndexBuffer*)malloc(sizeof(IndexBuffer));
    ib->count = count;
    GLCall(glGenBuffers(1, &ib->id));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib->id));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, ib->count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    return ib;

}
void bind_index_buffer(IndexBuffer* indexBuffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->id));
}
void unbind_index_buffer(){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

}
void free_index_buffer(IndexBuffer* indexBuffer){
    GLCall(glDeleteBuffers(1, &indexBuffer->id));
    free(indexBuffer);
}
