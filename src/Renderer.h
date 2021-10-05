#ifndef OPENGL_LEARNING_RENDERER_H
#define OPENGL_LEARNING_RENDERER_H

#include "GL/glew.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define ASSERT(x) if (!(x)) __debugbreak();
#else
#define ASSERT(x)
#endif

#define GLCall(x)   GLClearError(); \
                    x;\
                    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* func, const char* file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

#endif //OPENGL_LEARNING_RENDERER_H
