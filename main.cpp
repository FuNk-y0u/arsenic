#include <iostream>
#include <core.h>

#define sens 0.1f
#define speed 0.01f

int main()
{
    Window main_window = Window("Arsenic v0.0.1", 640, 480);
    
    bool running = true;
    
    SDL_Event window_event;


    const char* vertex_shader = 
"#version 430 core\n"
"layout(location=0) in vec2 position;\n"
"uniform mat4 u_ModelMatrix;\n"
"uniform mat4 u_PerspectiveMatrix;\n"
"uniform mat4 u_ViewMatrix;\n"
"void main(){\n"
"   gl_Position = u_PerspectiveMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 0.0f, 1.0f);\n"
"}\n";

    const char* fragment_shader= 
"#version 430 core\n"
"layout(location=0) out vec4 color;\n"
"void main(){\n"
"   color = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
"}\n";

    Renderer renderer = Renderer(
        (Rspec) {
            { {GL_FLOAT,2} },
            1000,
            { .vertex_shader = vertex_shader, .fragment_shader = fragment_shader} 
        }
    );

    Vertices positions = { 0.0f,  0.5f, -0.5f, -0.5f, 0.5f, -0.5f};
    
    Camera cam = Camera(80.0f, (float)640/(float)480, 0.1f, 50.0f, glm::vec3(0.0f, 0.0f, 5.0f));

    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int mouse_x, mouse_y;

    mouse_x = 0;
    mouse_y = 0;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    bool forward = false;
    bool backwards = false;
    bool left = false;
    bool right = false;

    while (running) {
        
        if(SDL_PollEvent(&window_event)){
            if(SDL_QUIT == window_event.type) {
                running = false;
            }

            mouse_x = window_event.motion.xrel;
            mouse_y = window_event.motion.yrel; 

            if(window_event.type == SDL_KEYDOWN){
                switch (window_event.key.keysym.sym) {
                    case SDLK_w:
                        forward = true;
                        break;
                    case SDLK_s:
                        backwards = true;
                        break;
                    case SDLK_a:
                        left = true;
                        break;
                    case SDLK_d:
                        right = true;
                        break;
                }

            }

            if(window_event.type == SDL_KEYUP){
                switch(window_event.key.keysym.sym){
                    case SDLK_w:
                        forward = false;
                        break;
                    case SDLK_s:
                        backwards = false;
                        break;
                    case SDLK_a:
                        left = false;
                        break;
                    case SDLK_d:
                        right = false;
                        break;

                }
            }
            if(window_event.type == SDL_MOUSEMOTION){

                glm::vec3 direction; 
                
                cam.yaw += mouse_x * sens;
                cam.pitch += mouse_y * sens;
                
                if (cam.pitch > 89.0f)
                    cam.pitch = 89.0f;
                if (cam.pitch < -89.0f)
                    cam.pitch = -89.0f;

                direction.x = cos(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
                direction.y = sin(glm::radians(cam.pitch));
                direction.z = sin(glm::radians(cam.yaw)) * cos(glm::radians(cam.pitch));
                cam.front = glm::normalize(direction); 
            }
        
        }

        if(forward == true)
        {
            cam.pos +=  cam.front * speed;
        }

        if(backwards == true)
        {
            cam.pos -= cam.front * speed;
        }

        if(left == true)
        {
            cam.pos += glm::cross(cam.up, cam.front) * speed;
        }

        if(right == true)
        {

            cam.pos += glm::cross(cam.front, cam.up) * speed;
        }

        renderer.begin();

        renderer.push_vertices(positions);
        cam.update(&renderer);

        renderer.end();

        SDL_GL_SwapWindow(main_window.sdl_window);
    }
}
