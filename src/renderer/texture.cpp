#include "texture.hpp"

#include <stdexcept>
#include <utility>

Texture::Texture(const void *data, int width, int height)
{
    if (data)
    {
        glGenTextures(1, &mID);
        Bind();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        throw std::runtime_error("Invalid texture data");
    }
}

Texture::Texture(Texture &&other)
    : mID(std::exchange(other.mID, 0)) {}

Texture &Texture::operator=(Texture &&other)
{
    std::swap(other, *this);
    return *this;
}

Texture::~Texture()
{
    glDeleteTextures(1, &mID);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}