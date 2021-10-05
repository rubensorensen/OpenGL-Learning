#ifndef OPENGL_LEARNING_VERTEXBUFFERLAYOUT_H
#define OPENGL_LEARNING_VERTEXBUFFERLAYOUT_H

#include "GL/glew.h"

#include "Renderer.h"

#include <vector>
#include <iostream>

struct VertexBufferElement
{
    unsigned int Type;
    unsigned int Count;
    unsigned char Normalized;

    static unsigned int GetTypeSize(unsigned int type);
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
            : m_Stride(0)
    {}

    template <typename T>
    void Push(unsigned int count);

    inline const std::vector<VertexBufferElement>& GetElements() const
    { return m_Elements; }

    inline unsigned int GetStride() const
    { return m_Stride; }

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
};


inline unsigned int VertexBufferElement::GetTypeSize(unsigned int type)
{
    switch (type)
    {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
    }
    ASSERT(false);
    return 0;
}

template<typename T>
inline void VertexBufferLayout::Push(unsigned int count)
{
    std::cout << "Unsupported type" << std::endl;
}

template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
}

template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
}


#endif //OPENGL_LEARNING_VERTEXBUFFERLAYOUT_H
