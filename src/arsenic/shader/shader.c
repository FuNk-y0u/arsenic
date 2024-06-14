#include "shader.h"
#include "error/error.h"

static unsigned int compile_shader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source;
	GLCall(glShaderSource(id, 1, &src, NULL));
	GLCall(glCompileShader(id));
		
	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if(result == GL_FALSE){
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));

		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		
		if(type == GL_VERTEX_SHADER){
			printf("[error] Failed to compile VERTEX SHADER\n");
		}
		else{
			printf("[error] Failed to compile FRAGMENT SHADER\n");
		}
		printf("[error] %s\n", message);
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

Shader* create_shader(const char* vertexShader, const char* fragmentShader){

    Shader* program = (Shader*)malloc(sizeof(Shader));
    program->id = GLCall(glCreateProgram());

    unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program->id, vs));
	GLCall(glAttachShader(program->id, fs));
	
	GLCall(glLinkProgram(program->id));
	GLCall(glValidateProgram(program->id));
	
	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

void bind_shader(Shader* program){
	GLCall(glUseProgram(program->id));
}

ShaderULocation* get_ul_shader(Shader* program, const char* name){
	ShaderULocation* location = (ShaderULocation*)malloc(sizeof(ShaderULocation));
	GLCall(location->id = glGetUniformLocation(program->id, name));
	assert(location->id != -1);
	return location;
}

void unbind_shader(){
	GLCall(glUseProgram(0));
}

void u4f_shader_set(ShaderULocation* location, float x, float y, float z, float w){
	GLCall(glUniform4f(location->id, x, y, z, w));
}

void u1i_shader_set(ShaderULocation* location, int x){
	GLCall(glUniform1i(location->id, x));
}

void free_shader(Shader* program){
	GLCall(glDeleteProgram(program->id));
	free(program);
}

void free_ul_shader(ShaderULocation* location){
	free(location);
}