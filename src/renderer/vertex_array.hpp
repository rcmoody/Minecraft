#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

#include "opengl.hpp"

struct VertexArrayDeleter
{
    void operator()(GLuint id)
    {
        glDeleteVertexArrays(1, &id);
    }
};

class VertexArray : public OpenGLObject<VertexArrayDeleter>
{
public:
    VertexArray();

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};