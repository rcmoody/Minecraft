#include "renderer.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils.hpp"

Renderer::Renderer()
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);

    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = Utils::ReadFile("res/shaders/vert.glsl");
    sources[GL_FRAGMENT_SHADER] = Utils::ReadFile("res/shaders/frag.glsl");
    mShader = std::make_optional<Shader>(sources);

    mTextureArray = std::make_optional<TextureArray>(Utils::LoadTextureArray(16, 16, {"res/images/grass_side.png", "res/images/grass_top.png", "res/images/dirt.png"}));
}

void Renderer::Draw(std::span<const Renderable> renderables, glm::mat4 view, glm::mat4 projection)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShader->Bind();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    for (auto &renderable : renderables)
        renderable.Render(mShader.value());
}

template <>
Mesh &Renderer::AddMesh<float>(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, VertexBufferLayout layout)
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

    mMeshes.emplace_back(std::move(mesh));
    return mMeshes.back();
}