#include "vertex_buffer.hpp"

VertexBuffer::VertexBuffer(const void *data, GLsizeiptr size)
    : Buffer(GL_ARRAY_BUFFER, data, size)
{
}