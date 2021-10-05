#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
    vb.Bind();
    const auto& elements{ layout.GetElements() };
    unsigned int offset{ 0 };
    for (size_t i{ 0 }; i < elements.size(); ++i)
    {
        const auto& element{ elements[i] };
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.Count, element.Type, element.Normalized, layout.GetStride(), reinterpret_cast<const void*>(offset)));
        offset += element.Count * VertexBufferElement::GetTypeSize(element.Type);
    }
}

