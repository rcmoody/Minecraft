#pragma once

#include <memory>

#include <glad/gl.h>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "texture_array.hpp"

class Renderer
{
    std::unique_ptr<VertexArray> mVertexArray;
    std::unique_ptr<VertexBuffer> mVertexBuffer;
    std::unique_ptr<IndexBuffer> mIndexBuffer;
    std::unique_ptr<Shader> mShader;
    std::unique_ptr<TextureArray> mTextureArray;
    float mTheta;

public:
    Renderer();

    void Draw(int screenWidth, int screenHeight);
};