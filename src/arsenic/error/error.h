#include <stdio.h>
#define GLCall(x)\
        (\
                clear_gl_error(), \
                x\
        );\
        gl_error_log(#x, __FILE__, __LINE__);\

static void clear_gl_error() {
        while(glGetError());
}

static int gl_error_log(const char* function, const char* file, int line) {
        GLenum error;
        while ((error = glGetError())) {
                printf("[Error code]: %d\n", error);
                printf("[Error message]: %s\n", gluErrorString(error));
                printf("[Opengl error]: %s %s: %d\n", function ,file, line);
                return 0;
        }
        return 1;
}