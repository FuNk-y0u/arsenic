#include "texture.h"
#include "STB/stb_image.h"
#include "error/error.h"

Texture* create_texture(const char* filePath){
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    Texture* tex = (Texture*)malloc(sizeof(Texture));

    stbi_set_flip_vertically_on_load(1);
    tex->imageStorage = stbi_load(filePath, &tex->width, &tex->height, &tex->bitPerPixel, 0);


    GLCall(glGenTextures(1, &tex->id));
    GLCall(glBindTexture(GL_TEXTURE_2D, tex->id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    if(tex->imageStorage){
    }
    else{
        printf("[error] image not loaded, please check your image file path \n");
    }

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex->width, tex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex->imageStorage));
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));

    if(tex->imageStorage){
        stbi_image_free(tex->imageStorage);
    }

    return tex;

}

Texture* free_texture(Texture* tex){
    GLCall(glDeleteTextures(1, tex->id));
    free(tex);
}

void bind_texture(Texture* tex, unsigned int slot){
    GLCall(glBindTextureUnit(tex->id, tex->id));
}

void unbind_texture(){
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}


