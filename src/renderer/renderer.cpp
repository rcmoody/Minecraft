#include "renderer.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils.hpp"

Renderer::Renderer()
    : mShader({{GL_VERTEX_SHADER, Utils::ReadFile("res/shaders/vert.glsl")},
               {GL_FRAGMENT_SHADER, Utils::ReadFile("res/shaders/frag.glsl")}}),
      mTextureArray(Utils::LoadTextureArray(16, 16, {"res/images/grass_side.png", "res/images/grass_top.png", "res/images/dirt.png"}))
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
}

void Renderer::Draw(std::span<const Renderable> renderables, glm::mat4 view, glm::mat4 projection)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShader.Bind();
    mShader.setMat4("view", view);
    mShader.setMat4("projection", projection);

    for (auto &renderable : renderables)
        renderable.Render(mMeshes, mShader);
}

ResourceHandle<Mesh> Renderer::AddMesh(std::span<float> vertices, std::span<unsigned int> indices, const VertexBufferLayout &layout)
{
    VertexArray vertexArray;

    VertexBuffer vertexBuffer(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(float)));
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices.data(), static_cast<GLuint>(indices.size()));

    Mesh mesh{
        std::move(vertexArray),
        std::move(vertexBuffer),
        std::move(indexBuffer),
    };

    return mMeshes.Add(std::move(mesh));
}