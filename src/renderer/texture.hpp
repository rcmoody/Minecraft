#pragma once

#include <string>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

struct TextureFormat
{
    int width;
    int height;
};

class Texture
{
public:
    Texture(const void *data, int width, int height);
    Texture(Texture &&other);
    Texture& operator=(Texture &&other);
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    ~Texture();

    void Bind();
    void Unbind();

private:
    GLuint mID;
};