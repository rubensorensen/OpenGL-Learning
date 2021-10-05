#include "Renderer.h"

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* func, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error 0x" << std::hex << error << std::dec << "] " << func << " " << file << ':' << line << std::endl;
        return false;
    }
    return true;
}