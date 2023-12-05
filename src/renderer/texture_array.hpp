#pragma once

#include <vector>
#include <string>

#include <glad/gl.h>

class TextureArray {
public:
    TextureArray(int width, int height, const std::vector<void *> &data);
    TextureArray(TextureArray &&other);
    TextureArray& operator=(TextureArray &&other);
    TextureArray(const TextureArray&) = delete;
    TextureArray& operator=(const TextureArray&) = delete;
    ~TextureArray();

    void Bind() const;
    void Unbind() const;

private:
    GLuint mID;
};