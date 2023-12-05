#pragma once

#include <glad/gl.h>

#include "opengl.hpp"

class Buffer : public OpenGLObject
{
    GLenum mTarget;

public:
    Buffer(GLenum target, const void *data, GLsizeiptr size);
    ~Buffer();
    Buffer(Buffer &&) = default;

    void Bind() const;
    void Unbind() const;
};