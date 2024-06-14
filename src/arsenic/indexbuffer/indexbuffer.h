#include "globalheader.h"

typedef struct{
    unsigned int id;
    unsigned int count;
} IndexBuffer;

IndexBuffer* create_index_buffer(unsigned int* data, unsigned int count);
void bind_index_buffer(IndexBuffer* indexBuffer);
void unbind_index_buffer();
void free_index_buffer(IndexBuffer* indexBuffer);