#pragma once

#include <span>

#include <glad/gl.h>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "texture_array.hpp"
#include "shader.hpp"

struct Mesh
{
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    void Render() const
    {
        vertexArray.Bind();
        indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    }
};

struct Renderable
{
    Mesh &mesh;
    glm::mat4 transform;

    void Render(Shader& shader) const
    {
        shader.setMat4("model", transform);
        mesh.Render();
    }
};

class Renderer
{
    std::vector<Mesh> mMeshes;
    std::optional<TextureArray> mTextureArray;
    std::optional<Shader> mShader;

public:
    Renderer();

    void Draw(std::span<const Renderable> renderables, glm::mat4 view, glm::mat4 projection);

    template <typename T>
    Mesh &AddMesh(const std::vector<T>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout layout);
};