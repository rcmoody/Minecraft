#pragma once

#include <glad/gl.h>

#include "opengl.hpp"

struct BufferDeleter
{
    void operator()(GLuint id)
    {
        glDeleteBuffers(1, &id);
    }
};

class Buffer : public OpenGLObject<BufferDeleter>
{
    GLenum mTarget;

public:
    Buffer(GLenum target, const void *data, GLsizeiptr size);

    void Bind() const;
    void Unbind() const;
};