#include "texture_array.hpp"

#include <stdexcept>

#include <stb_image.hpp>

TextureArray::TextureArray(int width, int height, const std::vector<void *> &data)
{
    glGenTextures(1, &mID);
    Bind();

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, width, height, static_cast<GLsizei>(data.size()), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (int i = 0; i < data.size(); ++i)
    {
        if (data[i])
        {
            glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data[i]);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            throw std::runtime_error("Invalid texture data");
        }
    }
}

TextureArray::~TextureArray()
{
    glDeleteTextures(1, &mID);
}

void TextureArray::Bind() const
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, mID);
}

void TextureArray::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}