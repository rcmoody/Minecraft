#include "vertex_buffer_layout.hpp"

template <>
void VertexBufferLayout::Push<GLfloat>(GLint size)
{
    mElements.emplace_back(VertexBufferElement{size, GL_FLOAT, GL_FALSE});
    mStride += size * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::Push<GLint>(GLint size)
{
    mElements.emplace_back(VertexBufferElement{size, GL_UNSIGNED_INT, GL_FALSE});
    mStride += size * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::Push<GLbyte>(GLint size)
{
    mElements.emplace_back(VertexBufferElement{size, GL_UNSIGNED_BYTE, GL_TRUE});
    mStride += size * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}