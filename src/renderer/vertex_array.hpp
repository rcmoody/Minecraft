#pragma once

#include <glad/gl.h>

#include "vertex_buffer.hpp"
#include "vertex_buffer_layout.hpp"

class VertexArray
{
    unsigned int mID;

public:
    VertexArray();
    VertexArray(VertexArray &&other);
    VertexArray &operator=(VertexArray &&other);
    VertexArray(const VertexArray &) = delete;
    VertexArray &operator=(const VertexArray &) = delete;
    ~VertexArray();

    void AddBuffer(const VertexBuffer &vertexBuffer, const VertexBufferLayout &layout);
    void Bind() const;
    void Unbind() const;
};