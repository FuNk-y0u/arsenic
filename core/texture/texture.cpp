#include "texture.h"

Texture::Texture(const char* image_path, bool flip){
    if(flip)
        stbi_set_flip_vertically_on_load(1);

    unsigned char* texture_data = stbi_load(image_path, &this->width, &this->height, &this->channels, 4);

    if(texture_data == NULL){
        std::cout << "ERROR: Texture image " << image_path << " unreadable " << std::endl;
        exit(-1);
    }
    
    glc(glGenTextures(1, &this->id));
    glc(glBindTexture(GL_TEXTURE_2D, this->id));

    glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    glc(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data));

    if(this->id)
    {
        stbi_image_free(texture_data);
    }
    else{
        std::cout << "ERROR: Unable to create texture from " << image_path << std::endl;
    }

    glc(glBindTexture(GL_TEXTURE_2D, 0));

}

void Texture::bind(){
    glc(glActiveTexture(GL_TEXTURE0 + (i32) this->id));
    glc(glBindTexture(GL_TEXTURE_2D, this->id));
}
