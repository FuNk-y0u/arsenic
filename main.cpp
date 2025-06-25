#include <iostream>
#include <core.h>

#define sens 0.5f
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

    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    int mouse_x, mouse_y;

    mouse_x = 0;
    mouse_y = 0;
    f32 offset = 0.0f;

    f32 yaw = -90.0f;
    f32 pitch = 0.0f;

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
                
                yaw += mouse_x * sens;
                pitch += mouse_y * sens;
                
                if (pitch > 89.0f)
                    pitch = 89.0f;
                if (pitch < -89.0f)
                    pitch = -89.0f;

                direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                direction.y = sin(glm::radians(pitch));
                direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
                center = glm::normalize(direction); 
            }

           

        }

        if(forward == true)
        {
            cam_pos +=  center * speed;
        }

        if(backwards == true)
        {
            cam_pos -= center * speed;
        }

        if(left == true)
        {
            cam_pos += glm::cross(up, center) * speed;
        }

        if(right == true)
        {

            cam_pos += glm::cross(center, up) * speed;
        }
        renderer.begin();

        renderer.push_vertices(positions);
        GLint model_matrix_location = glGetUniformLocation(renderer.render_shader.id, "u_ModelMatrix"); 

        if( model_matrix_location >= 0) {
        }
        else{
            std::cout << "UNIFORM: Canoot find u_ModelMatrix" << std::endl;
        }

        GLint perspective_matrix_location = glGetUniformLocation(renderer.render_shader.id, "u_PerspectiveMatrix");


        if( model_matrix_location >= 0) {
        }
        else{
            std::cout << "UNIFORM: Canoot find u_PerspectiveMatrix" << std::endl;
        }

        GLint view_matrix_location = glGetUniformLocation(renderer.render_shader.id, "u_ViewMatrix");


        if( view_matrix_location >= 0) {
        }
        else{
            std::cout << "UNIFORM: Canoot find u_ViewMatrix" << std::endl;
        }
        
        glm::mat4 perspective_matrix = glm::perspective(glm::radians(45.0f), (float)640/(float)480, 0.1f, 100.0f);
        glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.5f));
        glm::mat4 view_matrix = glm::lookAt(cam_pos,cam_pos + center, up);

        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &model_matrix[0][0]);
        glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, &perspective_matrix[0][0]);
        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &view_matrix[0][0]);
        

        renderer.end();

        SDL_GL_SwapWindow(main_window.sdl_window);
    }
}
