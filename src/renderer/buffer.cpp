#include "buffer.hpp"

#include <utility>

Buffer::Buffer(GLenum target, const void *data, GLsizeiptr size)
    : mTarget(target)
{
    glGenBuffers(1, &mID);
    Bind();
    glBufferData(mTarget, size, data, GL_STATIC_DRAW);
}

Buffer::Buffer(Buffer &&other)
    : mID(std::exchange(other.mID, 0)) {}

Buffer &Buffer::operator=(Buffer &&other)
{
    std::swap(other, *this);
    return *this;
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &mID);
}

void Buffer::Bind() const
{
    glBindBuffer(mTarget, mID);
}

void Buffer::Unbind() const
{
    glBindBuffer(mTarget, 0);
}