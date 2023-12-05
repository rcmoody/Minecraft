#pragma once

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "gl_object.hpp"

class Texture : public GLObject
{
public:
    Texture(const void *data, int width, int height);
    ~Texture();
    Texture(Texture &&) = default;

    void Bind();
    void Unbind();
};