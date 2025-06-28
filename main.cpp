#include <iostream>
#include <core.h>

#include "config.h"

int main()
{
    Window main_window = Window("Arsenic v0.0.1", WIDTH, HEIGHT);
    
    bool running = true;
    
    SDL_Event window_event;


    const char* vertex_shader = 
"#version 430 core\n"
"layout(location=0) in vec2 position;\n"
"layout(location=1) in vec2 tex_coords;\n"
"layout(location=2) in float tex_id;\n"

"uniform mat4 u_ModelMatrix;\n"
"uniform mat4 u_PerspectiveMatrix;\n"
"uniform mat4 u_ViewMatrix;\n"
"out vec2 v_tex_coords;\n"
"out float v_tex_id;\n"

"void main(){\n"
"   gl_Position = u_PerspectiveMatrix * u_ViewMatrix * u_ModelMatrix * vec4(position, 0.0f, 1.0f);\n"
"   v_tex_coords = tex_coords;\n"
"   v_tex_id = tex_id;\n"
"}\n";

    const char* fragment_shader= 
"#version 430 core\n"
"layout(location=0) out vec4 color;\n"
"in vec2 v_tex_coords;\n"
"in float v_tex_id;\n"
"uniform sampler2D textures[32];\n"
"void main(){\n"
"   int id = int(v_tex_id);\n"
"   color = texture(textures[id], v_tex_coords);\n"
"}\n";

    Renderer renderer = Renderer(
        (Rspec) {
            { {GL_FLOAT,2}, {GL_FLOAT, 2}, {GL_FLOAT,1}},
            1000,
            { .vertex_shader = vertex_shader, .fragment_shader = fragment_shader} 
        }
    );


    Vertices positions = {
        -0.5f,  0.5f,    0.0f, 1.0f,   1.0f, // Top Left
        -0.5f, -0.5f,    0.0f, 0.0f,   1.0f, // Bottom Left
        0.5f,  0.5f,    1.0f, 1.0f,   1.0f, // Top Right

        -0.5f, -0.5f,    0.0f, 0.0f,   1.0f, // Bottom Left
        0.5f, -0.5f,    1.0f, 0.0f,   1.0f, // Bottom Right
        0.5f,  0.5f,    1.0f, 1.0f,   1.0f  // Top Right
    };

    Texture tex = Texture("bin/error.png", true);
    
    Camera cam = Camera(80.0f, (float)WIDTH/(float)HEIGHT, NEAR_PLANE, FAR_PLANE, glm::vec3(0.0f, 0.0f, 5.0f));

    int mouse_x, mouse_y;

    SDL_SetRelativeMouseMode(SDL_TRUE);

    bool forward = false;
    bool backwards = false;
    bool left = false;
    bool right = false;

   i32 samplers[32];

    for (int i = 0; i < 32; i++) {
        samplers[i] = i;
    }


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
                cam.pitch -= mouse_y * sens;
                
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

        tex.bind();

        renderer.push_vertices(positions);

        i32 tex_loc = glc(glGetUniformLocation(renderer.render_shader.id, "textures"));
        if (tex_loc < 0) {
            std::cout << "ERROR: Counot find uniform location for textures" << std::endl;
        }
        glc(glUniform1iv(tex_loc, 32, &samplers[0]));

        cam.update(&renderer);

        renderer.end();

        SDL_GL_SwapWindow(main_window.sdl_window);
    }
}
