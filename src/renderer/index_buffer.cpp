#include "index_buffer.hpp"

IndexBuffer::IndexBuffer(const GLuint *data, GLuint count)
    : Buffer(GL_ELEMENT_ARRAY_BUFFER, data, count * sizeof(GLuint)), mCount(count)
{
}