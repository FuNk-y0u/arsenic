#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<GL/glew.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_opengl.h>

// ---------------------------- ERROR SYSTEM --------------------//
#define ASSERT(x) if(!(x)) exit(1);
#define GLCall(x) clearError(); \
x;\
ASSERT(ErrorLog(#x, __FILE__, __LINE__))

static void clearError()
{
	while(glGetError());
}

static int ErrorLog(const char* function, const char* file, int line)
{
	GLenum error;
	while(error = glGetError())
	{
		fprintf(stderr, "[ERROR CODE]: %s \n", error);
		fprintf(stderr, "[OPENGL ERROR]: %s %s: %d\n", function ,file, line);
		return -1;
	}
	return 1;
}

// -------------------------- SHADER CODE -------------------- //
unsigned int a_compile_shader(unsigned int type, char* shader_src)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &shader_src, NULL);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*) calloc(length, sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		fprintf(stderr, "[SHADER ERROR] FAILED TO COMPILE SHADER %s\n", (type == GL_VERTEX_SHADER ? "Vertex": "Fragment"));
		fprintf(stderr, "%s\n", message);

		glDeleteShader(id);
		return 0;
	}

	return id;

}

int a_Create_Shader(char* vertex_shader, char* fragment_shader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = a_compile_shader(GL_VERTEX_SHADER, vertex_shader);
	unsigned int fs = a_compile_shader(GL_FRAGMENT_SHADER, fragment_shader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	
	return program;
}
// -------------------- INIT AND ERROR HANDELING -----------//


int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window* aWindow = NULL;
SDL_GLContext aContext;

int a_running = 1;

SDL_Event a_Event;

void a_Clear(){
	SDL_DestroyWindow(aWindow);
	aWindow = NULL;
	SDL_Quit();
}

void a_GL_Version(){
	printf("ARSENIC RUNNING ON : %s\n", glGetString(GL_VERSION));
}

void a_SDL_Error(){
	printf("[ARSENIC ERROR SDL] %s", SDL_GetError());
}

int a_Init(void)
{
	// SDL INIT
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		a_SDL_Error();
		return -1;
	}

	// SPECIFY OPENGL VERSION
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// CREATING WINDOW AND CONTEXT
	aWindow = SDL_CreateWindow("Arsenic", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	aContext = SDL_GL_CreateContext(aWindow);


	// CHECKING FOR ERROR
	if(aWindow == NULL)
	{
		a_SDL_Error();
		return -1;
	}

	if(aContext == NULL)
	{
		a_SDL_Error();
		return -1;
	}

	if(glewInit() != GLEW_OK)
	{
		printf("[ARSENIC GL INIT ERROR]");		
	}

	// PRINTING GL VERSION
	a_GL_Version();

}


// --------------------- MAIN PROGRAM -------------------//
int main(int argc, char* args[]){

	// INITIALIZING ARSENIC
	if(a_Init() == -1){
		printf("[ARSENIC INIT ERROR]");
	}
	
	// VERTICES OF TRIANGLE	
	float vertex[] = {
		-0.1f, -0.1f, // 0
		0.1f, -0.1f, // 1
		0.1f, 0.1f, // 2
		-0.1f, 0.1f, // 3
	};
	
	unsigned int indices[] = 
	{
		0,1,2,
		2,3,0
	};

	// vertex array object
	unsigned int vao;
	GLCall(glGenVertexArrays(1,&vao));
	GLCall(glBindVertexArray(vao));

	// CREATING A BUFFER
	unsigned int aBuffer;
	GLCall(glGenBuffers(1, &aBuffer));

	// CHOOSING BUFFER
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, aBuffer));

	// ADDING DATA TO BUFFER
	GLCall(glBufferData(GL_ARRAY_BUFFER, 6 * 2 * sizeof(float), vertex, GL_STATIC_DRAW));
	
	// SETTING LAYOUT
	// OF CURRENTLY BINDED BUFFER
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0));
	// ENABLEING THE REQUIRED VERTEX ARRAY
	GLCall(glEnableVertexAttribArray(0));

	// index buffer stuff	
	unsigned int ibo;
	GLCall(glGenBuffers(1, &ibo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));


	char* vertexShader = 
		"#version 120\n"
		"void main(void)\n"
		"{\n"
		"	gl_Position = ftransform();\n"
		"}\n";
	
	char* fragmentShader = 
		"#version 120\n"
		"uniform vec4 u_Color;\n"
		"void main(void)\n"
		"{\n"
		"	gl_FragColor = u_Color;\n"
		"}\n";

	unsigned int shader = a_Create_Shader(vertexShader, fragmentShader);
	GLCall(glUseProgram(shader));
	
	int location = glGetUniformLocation(shader, "u_Color");
	if( location == -1)
	{
		printf("[INFO] var doesnot exists\n");
	}
	
	float r = 1.0f;
	float g = 1.0f;
	float b = 0.0f;
	
	GLCall(glUseProgram(0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindVertexArray(0));
	// MAIN LOOP
	while(a_running)
	{
		while(SDL_PollEvent(&a_Event) != 0)
		{
			switch(a_Event.type)
			{
				case SDL_QUIT:
					a_running = 0;
					break;				
			}

			GLCall(glUseProgram(shader));
			GLCall(glBindVertexArray(vao));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
			
			GLCall(glUniform4f(location, r, g, b, 1.0f));
			GLCall(glClear(GL_COLOR_BUFFER_BIT));


			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));	
			// SWAPPING BACK BUFFER AND FRONT BUFFER
			SDL_GL_SwapWindow(aWindow);
		}
	}

	// CLEAN UP
	a_Clear();
	
	return 0;
}
