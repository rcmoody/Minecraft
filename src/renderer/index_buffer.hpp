#pragma once

#include <glad/gl.h>

#include "buffer.hpp"

class IndexBuffer : public Buffer
{
    GLuint mCount;

public:
    IndexBuffer(const GLuint *data, GLuint count);

    unsigned int GetCount() const
    {
        return mCount;
    }
};