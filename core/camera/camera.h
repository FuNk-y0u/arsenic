#pragma once

#include <common.h>
#include <error/error.h>
#include <renderer/renderer.h>


class Camera{
    public:
        f32 fov;
        f32 aspect_ratio;
        f32 near_plane;
        f32 far_plane;

        glm::vec3 pos;
        glm::vec3 front;
        glm::vec3 up;

        f32 yaw;
        f32 pitch;

        Camera(f32 fov, f32 aspect_ratio, f32 near_plane, f32 far_plane, glm::vec3 pos);
        void update(Renderer* renderer);
    private:
        void set_uniform_matrix(i32 shader_id, const char* name, glm::mat4 matrix);
};
