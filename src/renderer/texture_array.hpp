#pragma once

#include <vector>
#include <string>

#include <glad/gl.h>

#include "opengl.hpp"

class TextureArray : public OpenGLObject {
public:
    TextureArray(int width, int height, const std::vector<void *> &data);
    ~TextureArray();
    TextureArray(TextureArray &&) = default;

    void Bind() const;
    void Unbind() const;
};