#pragma once

#include <vector>
#include <string>

#include <glad/gl.h>

#include "gl_object.hpp"

class TextureArray : public GLObject {
public:
    TextureArray(int width, int height, const std::vector<void *> &data);
    ~TextureArray();

    void Bind() const;
    void Unbind() const;
};