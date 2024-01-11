#pragma once

#include <vector>
#include <string>

#include <glad/gl.h>

#include "opengl.hpp"

struct TextureArrayDeleter
{
    void operator()(GLuint id)
    {
        glDeleteTextures(1, &id);
    }
};

class TextureArray : public OpenGLObject<TextureArrayDeleter> {
public:
    TextureArray(int width, int height, const std::vector<void *> &data);

    void Bind() const;
    void Unbind() const;
};