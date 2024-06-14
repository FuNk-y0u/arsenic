 #include "vertexarray.h"
#include "error/error.h"

VertexArray* create_vertex_array(){
    VertexArray* va = (VertexArray*)malloc(sizeof(VertexArray));
    GLCall(glGenVertexArrays(1, &va->id));
    GLCall(glBindVertexArray(va->id));
    return va;
}

void vertex_array_pushf(VertexArrayItem* layout[]){
    int length = sizeof(layout)/sizeof(layout[0]);
    unsigned int stride = 0;
    unsigned int offset = 0;

    // calculating stride
    for( int i = 0; i <= (length); i ++){
        stride += sizeof(layout[i]->type) * (layout[i]->number);
    }

    for(int i = 0; i<= length; i++){
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, layout[i]->number, layout[i]->type, GL_FALSE, stride, (const void*) offset));

        offset += sizeof(layout[i]->type) * layout[i]->number;
    }
}

VertexArrayItem* create_vertex_array_item(unsigned int number, unsigned int type){
    VertexArrayItem* item = (VertexArrayItem*)malloc(sizeof(VertexArrayItem));
    item->number = number;
    item->type = type;
    return item;
}

void unbind_vertex_array(){
    GLCall(glBindVertexArray(0));
}

void bind_vertex_array(VertexArray* vertexArray){
    GLCall(glBindVertexArray(vertexArray->id));
}

void free_vertex_array(VertexArray* vertexArray){
    glDeleteBuffers(1, &vertexArray->id);
    free(vertexArray);
}

void free_vertex_array_items(VertexArrayItem* items[]){
    int length = sizeof(items)/sizeof(items[0]);

    for( int i = 0; i <= (length); i ++){
        free(items[i]);
    }
}