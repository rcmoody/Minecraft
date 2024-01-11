#include "vertex_array.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &mID);
}

void VertexArray::AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout)
{
    Bind();
    vertexBuffer.Bind();
    const auto &elements = layout.GetElements();
    int offset = 0;
    for (unsigned int i = 0; i < elements.size(); ++i)
    {
        const auto &element = elements[i];
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.size, element.type, element.normalized,
                              layout.GetStride(), reinterpret_cast<void *>(offset));
        offset += element.size * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(mID);
}

void VertexArray::Unbind() const
{
    glBindVertexArray(0);
};