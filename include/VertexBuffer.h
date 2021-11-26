#ifndef OPENGL_LEARNING_VERTEXBUFFER_H
#define OPENGL_LEARNING_VERTEXBUFFER_H

#include "pch.h"

class VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int m_RendererID;
};

#endif // OPENGL_LEARNING_VERTEXBUFFER_H
