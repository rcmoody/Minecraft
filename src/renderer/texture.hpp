#pragma once

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "opengl.hpp"

class Texture : public OpenGLObject
{
public:
    Texture(const void *data, int width, int height);
    ~Texture();
    Texture(Texture &&) = default;

    void Bind();
    void Unbind();
};