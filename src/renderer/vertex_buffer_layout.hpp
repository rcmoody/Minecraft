#pragma once

#include <vector>

#include <glad/gl.h>

struct VertexBufferElement
{
    GLint size;
    GLenum type;
    GLboolean normalized;

    static unsigned int GetSizeOfType(GLuint type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return sizeof(GLfloat);
        case GL_UNSIGNED_INT:
            return sizeof(GLuint);
        case GL_UNSIGNED_BYTE:
            return sizeof(GLbyte);
        }
        return 0;
    }
};

class VertexBufferLayout
{
    unsigned int mStride;
    std::vector<VertexBufferElement> mElements;

public:
    VertexBufferLayout() : mStride(0) {}

    template <typename T>
    void Push(GLint size);

    const std::vector<VertexBufferElement> GetElements() const { return mElements; };
    unsigned int GetStride() const { return mStride; };
};

template <>
void VertexBufferLayout::Push<GLfloat>(GLint size);

template <>
void VertexBufferLayout::Push<GLint>(GLint size);

template <>
void VertexBufferLayout::Push<GLbyte>(GLint size);