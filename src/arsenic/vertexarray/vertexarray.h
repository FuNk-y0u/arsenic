#include "globalheader.h"

typedef struct {
    unsigned int id;
} VertexArray;

typedef struct {
    unsigned int number;
    unsigned int type;
} VertexArrayItem;

VertexArray* create_vertex_array();
void vertex_array_pushf(VertexArrayItem* layout[]);
VertexArrayItem* create_vertex_array_item(unsigned int number, unsigned int type);
void unbind_vertex_array();
void bind_vertex_array(VertexArray* vertexArray);
void free_vertex_array(VertexArray* vertexArray);

