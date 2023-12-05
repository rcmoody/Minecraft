#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

#include "opengl.hpp"

class VertexArray : public OpenGLObject
{
public:
    VertexArray();
    ~VertexArray();
    VertexArray(VertexArray &&) = default;

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};