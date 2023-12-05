#pragma once

#include <glad/gl.h>

#include "gl_object.hpp"

class Buffer : public GLObject
{
    GLenum mTarget;

public:
    Buffer(GLenum target, const void *data, GLsizeiptr size);
    ~Buffer();
    Buffer(Buffer &&) = default;

    void Bind() const;
    void Unbind() const;
};