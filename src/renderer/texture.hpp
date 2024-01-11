#pragma once

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "opengl.hpp"

struct TextureDeleter
{
    void operator()(GLuint id)
    {
        glDeleteTextures(1, &id);
    }
};

class Texture : public OpenGLObject<TextureDeleter>
{
public:
    Texture(const void *data, int width, int height);

    void Bind();
    void Unbind();
};