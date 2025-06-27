#pragma once

#include <common.h>
#include <error/error.h>

// TODO add exit function to delete the texture from gpu memory
class Texture {
    public:
        u32 id;
        i32 width;
        i32 height;
        i32 channels;

        Texture(const char* image_path, bool flip);
        void bind();

};
