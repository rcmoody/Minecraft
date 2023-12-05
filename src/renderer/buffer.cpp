#include "buffer.hpp"

Buffer::Buffer(GLenum target, const void *data, GLsizeiptr size)
    : mTarget(target)
{
    glGenBuffers(1, &mID);
    Bind();
    glBufferData(mTarget, size, data, GL_STATIC_DRAW);
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