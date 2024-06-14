#include "window/window.h"
#include "vertexbuffer/vertexbuffer.h"
#include "indexbuffer/indexbuffer.h"
#include "vertexarray/vertexarray.h"
#include "shader/shader.h"
#include "texture/texture.h"

void draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader);
void clear();
void exit_arsenic(const VertexBuffer* vb,const VertexArray* va, const IndexBuffer* ib, const Shader* shader, const Window* window);