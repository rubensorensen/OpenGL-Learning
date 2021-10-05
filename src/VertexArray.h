#ifndef OPENGL_LEARNING_VERTEXARRAY_H
#define OPENGL_LEARNING_VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
    unsigned int m_RendererID;

};


#endif //OPENGL_LEARNING_VERTEXARRAY_H