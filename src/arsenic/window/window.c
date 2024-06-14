#include "window.h"

Window* window_new(const char* title, int width, int height){
	Window* window = (Window*)malloc(sizeof(Window));

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_Window *sdlWindow = SDL_CreateWindow(
			title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
	);

	// TODO create a basic log system
	if(sdlWindow == NULL){
		printf("[error] unable to create sdl window: %s \n", SDL_GetError());
	}

	SDL_GLContext _glContext = SDL_GL_CreateContext(sdlWindow);
	SDL_GL_SetSwapInterval(1);

	if(glewInit() != GLEW_OK){
		printf("[error] Unable to initialize glew\n");
	}
	
	printf("[info] Arsenic running on \n");
	printf("%s \n", glGetString(GL_VERSION));

	window->window = sdlWindow;
	window->width = width;
	window->height = height;
	return window;
}

void window_update(Window* window){
	SDL_GL_SwapWindow(window->window);
}

void free_window(Window* window){
	SDL_DestroyWindow(window->window);
	SDL_Quit();
	free(window);
}