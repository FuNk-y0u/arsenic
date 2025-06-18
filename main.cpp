#include <iostream>
#include <core.h>

int main()
{
    Window main_window = Window("Arsenic v0.0.1", 640, 480);
    
    bool running = true;
    
    SDL_Event window_event;

    Renderer renderer = Renderer(
        (Rspec) {
            { {GL_FLOAT,2} },
            1000,
            { .vertex_shader = "", .fragment_shader = ""}
        }
    );

    while (running) {
        if(SDL_PollEvent(&window_event)){
            if(SDL_QUIT == window_event.type) {
                running = false;
            }
        }

        renderer.begin();
        renderer.end();

        SDL_GL_SwapWindow(main_window.sdl_window);
    }
}
