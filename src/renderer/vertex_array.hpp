#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

#include "gl_object.hpp"

class VertexArray : public GLObject
{
public:
    VertexArray();
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};