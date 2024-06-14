#include "globalheader.h"
#include <assert.h>

typedef struct{
    unsigned int id;
} Shader;

typedef struct{
    int id;
} ShaderULocation;


Shader* create_shader(const char* vertexShader, const char* fragmentShader);
static unsigned int compile_shader(unsigned int type, const char* source);
void bind_shader(Shader* program);
ShaderULocation* get_ul_shader(Shader* program, const char* name);
void unbind_shader();
void u4f_shader_set(ShaderULocation* location, float x, float y, float z, float w);
void u1i_shader_set(ShaderULocation* location, int x);
void free_shader(Shader* program);
void free_ul_shader(ShaderULocation* location);