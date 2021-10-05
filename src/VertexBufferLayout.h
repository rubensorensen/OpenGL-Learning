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

    static unsigned int GetTypeSize(unsigned int type)
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
};

class VertexBufferLayout
{
public:
    VertexBufferLayout()
            : m_Stride(0)
    {}

    template<typename T>
    void Push(unsigned int count)
    {
        std::cout << "Unsupported type" << std::endl;
    }

    template<>
    void Push<float>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
    }

    template<>
    void Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
    }

    template<>
    void Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
        m_Stride += count * VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement>& GetElements() const
    { return m_Elements; }

    inline unsigned int GetStride() const
    { return m_Stride; }

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
};


#endif //OPENGL_LEARNING_VERTEXBUFFERLAYOUT_H
