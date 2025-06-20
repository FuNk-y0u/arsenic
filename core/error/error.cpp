#include "error.h"

void gl_clear_error(){
    while(glGetError() != GL_NO_ERROR){
    }
}

void gl_get_error(const char* function, const char* file, int line) {
    GLenum error = glGetError();
    while(error){
        std::cout << std::hex << error << std::endl;
        std::cout << "ERROR: " << gluErrorString(error) << std::endl;
        std::cout << "ERROR: " << function << " " << file << ":" << line << std::endl;
    }
}

