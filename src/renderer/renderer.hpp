#pragma once

#include <span>
#include <unordered_map>
#include <optional>

#include <glad/gl.h>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "texture_array.hpp"
#include "shader.hpp"

struct Mesh;

template <typename T>
class ResourceHandle
{
    unsigned int mID;

public:
    ResourceHandle(unsigned int id)
        : mID(id)
    {
    }

    unsigned int GetID() const
    {
        return mID;
    }
};

template <typename T>
class ResourceStorage
{
    std::unordered_map<unsigned int, T> mResources;
    unsigned int mNextID;

public:
    ResourceStorage()
        : mNextID(0)
    {
    }

    ResourceHandle<T> Add(T&& resource)
    {
        unsigned int id = mNextID;
        mResources.emplace(id, std::move(resource));
        mNextID++;
        return ResourceHandle<T>(id);
    }

    const T &Get(ResourceHandle<T> handle) const
    {
        return mResources.at(handle.GetID());
    }

    void Remove(ResourceHandle<T> handle)
    {
        mResources.erase(handle.GetID());
    }
};

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
    ResourceHandle<Mesh> mesh;
    glm::mat4 transform;

    void Render(const ResourceStorage<Mesh>& mMeshes, Shader &shader) const
    {
        shader.setMat4("model", transform);
        mMeshes.Get(mesh).Render();
    }
};

class Renderer
{
    ResourceStorage<Mesh> mMeshes;
    std::optional<TextureArray> mTextureArray;
    std::optional<Shader> mShader;

public:
    Renderer();

    void Draw(std::span<const Renderable> renderables, glm::mat4 view, glm::mat4 projection);

    template <typename T>
    ResourceHandle<Mesh> AddMesh(const std::vector<T> &vertices, const std::vector<unsigned int> &indices, const VertexBufferLayout &layout);
};