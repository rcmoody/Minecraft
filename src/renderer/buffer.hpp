#pragma once

#include <glad/gl.h>

class Buffer
{
    GLenum mTarget;

protected:
    GLuint mID;

public:
    Buffer(GLenum target, const void *data, GLsizeiptr size);
    Buffer(Buffer &&other);
    Buffer& operator=(Buffer &&other);
    Buffer(const Buffer&) = delete;
    Buffer& operator=(const Buffer&) = delete;
    ~Buffer();

    void Bind() const;
    void Unbind() const;
};