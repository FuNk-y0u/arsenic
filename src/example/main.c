#include <stdio.h>

#include "GL/glew.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_opengl.h"

#include "arsenic.h"

#include "error/error.h"



int main(int argc, char *argv[]){

	Window* window = window_new("Arsenic Test", 640, 480);

	int running = 1;

	float vertexs[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	VertexArray* vertexArray = create_vertex_array();

	VertexBuffer* vertexBuffer = create_vertex_buffer(&vertexs, 4 * 4 * sizeof(float));
	IndexBuffer* indexBuffer = create_index_buffer(&indices, 6);
	
	VertexArrayItem* vertexArrayItems[] = {create_vertex_array_item(2, GL_FLOAT), create_vertex_array_item(2, GL_FLOAT)};

	vertex_array_pushf(vertexArrayItems);
	free_vertex_array_items(vertexArrayItems);

	const char* vertexShader = 
		"#version 330 core\n"
		"layout(location = 0) in vec2 position;\n" //accesing from the vertex buffer
		"layout(location = 1) in vec2 texCoord;\n"
		"out vec2 v_TexCoord;\n"
		"void main(){\n"
		"	gl_Position = vec4(position, 0.0, 1.0);\n"
		"	v_TexCoord = texCoord;\n"
		"}\n";


	const char* fragmentShader = 
		"#version 330 core\n"
		"layout(location = 0) out vec4 color;\n"
		"in vec2 v_TexCoord;\n"
		"uniform sampler2D u_Texture;\n"
		"void main(){\n"
		"	vec4 texColor = texture(u_Texture, v_TexCoord);\n"
		"	color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * texColor;\n"
		"}\n";
	
	
	Shader* shader = create_shader(vertexShader, fragmentShader);
	bind_shader(shader);

	Texture* texture = create_texture("res/error.png");
	bind_texture(texture, texture->id);

	ShaderULocation* tex_location = get_ul_shader(shader, "u_Texture");

	SDL_Event windowEvent;

	while(running == 1){
		clear();

		if(SDL_PollEvent( &windowEvent)){
			if(SDL_QUIT == windowEvent.type){
				running = 0;
			}
        	}
		u1i_shader_set(tex_location, texture->id);

		draw(vertexArray, indexBuffer, shader);

		window_update(window);
	}

	free_ul_shader(tex_location);
	exit_arsenic(vertexBuffer, vertexArray, indexBuffer, shader, window);

	return 1;
}
