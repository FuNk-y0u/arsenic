#include "camera.h"

Camera::Camera(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane, glm::vec3 pos) {
    this->fov = fov;
    this->aspect_ratio = aspect_ratio;
    this->near_plane = near_plane;
    this->far_plane = far_plane;

    this->pos = pos;
    this->front = glm::vec3(0.0f, 0.0f, 0.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = -90.0f;
    this->pitch = 0.0f;
}

void Camera::set_uniform_matrix(i32 shader_id, const char* name, glm::mat4 matrix){
    GLint location = glGetUniformLocation(shader_id, name);

    if(location < 0) {
        std::cout << "ERROR: Cannot find uniform " << name << std::endl;
    }

    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}
void Camera::update(Renderer* renderer){
    glm::mat4 perspective_matrix = glm::perspective(glm::radians(this->fov), this->aspect_ratio, this->near_plane, this->far_plane);
    glm::mat4 model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    glm::mat4 view_matrix = glm::lookAt(this->pos, this->pos + this->front, this->up);

    this->set_uniform_matrix(renderer->render_shader.id, "u_ModelMatrix", model_matrix);
    this->set_uniform_matrix(renderer->render_shader.id, "u_PerspectiveMatrix", perspective_matrix);
    this->set_uniform_matrix(renderer->render_shader.id, "u_ViewMatrix", view_matrix);

}
