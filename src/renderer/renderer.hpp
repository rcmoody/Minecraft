#pragma once

#include <span>

#include <glad/gl.h>

#include "vertex_array.hpp"
#include "vertex_buffer.hpp"
#include "index_buffer.hpp"
#include "shader.hpp"
#include "texture_array.hpp"

struct Mesh
{
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    TextureArray textureArray;
    Shader shader;

    void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection) const
    {
        shader.Bind();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        vertexArray.Bind();
        indexBuffer.Bind();

        glDrawElements(GL_TRIANGLES, indexBuffer.GetCount(), GL_UNSIGNED_INT, nullptr);
    }
};

struct Renderable
{
    Mesh mesh;
    glm::mat4 transform;

    void Render(glm::mat4 view, glm::mat4 projection) const
    {
        mesh.Render(transform, view, projection);
    }
};

class Renderer
{
public:
    std::vector<Renderable> mRenderables;
    
    Renderer();

    void Draw(glm::mat4 view, glm::mat4 projection);
};