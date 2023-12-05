#pragma once

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <stb_image.hpp>

#include "renderer/texture.hpp"
#include "renderer/texture_array.hpp"

namespace Utils
{
    std::string ReadFile(const std::string &filename)
    {
        std::ifstream file(filename);

        if (!file.is_open())
        {
            throw std::ios_base::failure("Failed to open file: " + filename);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        return buffer.str();
    }

    std::unique_ptr<Texture> LoadTextureData(const std::string &filename)
    {
        stbi_set_flip_vertically_on_load(true);
        int width, height;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, nullptr, STBI_rgb_alpha);

        auto texture = std::make_unique<Texture>(data, width, height);

        stbi_image_free(data);

        return texture;
    }

    std::unique_ptr<TextureArray> LoadTextureArray(int width, int height, const std::vector<std::string> &filenames)
    {
        stbi_set_flip_vertically_on_load(true);
        std::vector<void *> textureArrayData;
        for (auto &filename : filenames)
        {
            int width, height;
            unsigned char *data = stbi_load(filename.c_str(), &width, &height, nullptr, STBI_rgb_alpha);
            textureArrayData.emplace_back(data);
        }

        auto textureArray = std::make_unique<TextureArray>(width, height, textureArrayData);

        for (auto &data : textureArrayData)
        {
            stbi_image_free(data);
        }

        return textureArray;
    }
}