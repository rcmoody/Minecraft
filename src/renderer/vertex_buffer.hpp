#pragma once

#include <glad/gl.h>

#include "buffer.hpp"

class VertexBuffer : public Buffer
{
public:
    VertexBuffer(const void *data, GLsizeiptr size);
    VertexBuffer(VertexBuffer &&) = default;
};