#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "globalheader.h"

typedef struct {
    SDL_Window* window;
    int width, height;
} Window;

Window* window_new(const char* title, int width, int height);
void free_window(Window* window);
void window_update(Window* window);