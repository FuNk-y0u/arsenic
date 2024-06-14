#include "globalheader.h"


typedef struct{
    unsigned int id;
    const char* filePath;
    unsigned char* imageStorage;
    int width;
    int height;
    int bitPerPixel;
} Texture;

Texture* create_texture(const char* filePath);
Texture* free_texture(Texture* tex);

void bind_texture(Texture* text, unsigned int slot);
void unbind_texture();
