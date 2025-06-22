#include <iostream>
#include <core.h>

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

    f32 offset = -1.50f;

    glm::vec3 cam_pos = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 center = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
   

    while (running) {
        if(SDL_PollEvent(&window_event)){
            if(SDL_QUIT == window_event.type) {
                running = false;
            }

            if(window_event.type == SDL_KEYDOWN){
                switch (window_event.key.keysym.sym) {
                    case SDLK_w:
                        offset -= 0.01f;
                        break;
                    case SDLK_s:
                        offset += 0.01f;
                        break;
                }
            }
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
        
        glm::mat4 perspective_matrix = glm::perspective(glm::radians(45.0f), (float)640/(float)480, 0.1f, 10.0f);
        glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, offset));
        glm::mat4 view_matrix = glm::lookAt(cam_pos, center, up);

        glUniformMatrix4fv(model_matrix_location, 1, GL_FALSE, &model_matrix[0][0]);
        glUniformMatrix4fv(perspective_matrix_location, 1, GL_FALSE, &perspective_matrix[0][0]);
        glUniformMatrix4fv(view_matrix_location, 1, GL_FALSE, &view_matrix[0][0]);
        

        renderer.end();

        SDL_GL_SwapWindow(main_window.sdl_window);
    }
}
