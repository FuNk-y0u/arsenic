#include "window.h"

Window::Window(std::string name, int width, int height){

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    this->width = width;
    this->height = height;
    this->name = name;
    this->sdl_window = SDL_CreateWindow(
            name.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width,
            height,
            SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_OPENGL
    );
    this->gl_context = SDL_GL_CreateContext(this->sdl_window);

    if(this->sdl_window == NULL){
        std::cout << "UNABLE TO MAKE WINDOW" << std::endl;
    }

    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)){
        std::cout << "Faile to initalize glad" << std::endl;
    }

}


Window::~Window(){

}
