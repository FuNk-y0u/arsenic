#include <common.h>
#include <SDL2/SDL.h>

class Window {
    public:
        std::string name;
        int width;
        int height; 

        SDL_Window* sdl_window;
        SDL_GLContext gl_context;
        
        Window(std::string name, int width, int height);
        ~Window();
};

