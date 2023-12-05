#include "renderer.hpp"

#include <spdlog/spdlog.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils.hpp"

Renderer::Renderer()
    : mTheta(0.0f)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = Utils::ReadFile("res/shaders/vert.glsl");
    sources[GL_FRAGMENT_SHADER] = Utils::ReadFile("res/shaders/frag.glsl");
    mShader = std::make_unique<Shader>(sources);

    std::vector<float> vertices = {
        // Front
        0.5, -0.5, 0.5, 1.0, 0.0, 0.0,
        0.5, 0.5, 0.5, 1.0, 1.0, 0.0,
        -0.5, 0.5, 0.5, 0.0, 1.0, 0.0,
        -0.5, -0.5, 0.5, 0.0, 0.0, 0.0,

        // Back
        -0.5, -0.5, -0.5, 1.0, 0.0, 0.0,
        -0.5, 0.5, -0.5, 1.0, 1.0, 0.0,
        0.5, 0.5, -0.5, 0.0, 1.0, 0.0,
        0.5, -0.5, -0.5, 0.0, 0.0, 0.0,

        // Left
        -0.5, -0.5, 0.5, 1.0, 0.0, 0.0,
        -0.5, 0.5, 0.5, 1.0, 1.0, 0.0,
        -0.5, 0.5, -0.5, 0.0, 1.0, 0.0,
        -0.5, -0.5, -0.5, 0.0, 0.0, 0.0,

        // Right
        0.5, -0.5, -0.5, 1.0, 0.0, 0.0,
        0.5, 0.5, -0.5, 1.0, 1.0, 0.0,
        0.5, 0.5, 0.5, 0.0, 1.0, 0.0,
        0.5, -0.5, 0.5, 0.0, 0.0, 0.0,

        // Top
        0.5, 0.5, -0.5, 1.0, 0.0, 1.0,
        -0.5, 0.5, -0.5, 1.0, 1.0, 1.0,
        -0.5, 0.5, 0.5, 0.0, 1.0, 1.0,
        0.5, 0.5, 0.5, 0.0, 0.0, 1.0,

        // Bottom
        0.5, -0.5, 0.5, 1.0, 0.0, 2.0,
        -0.5, -0.5, 0.5, 1.0, 1.0, 2.0,
        -0.5, -0.5, -0.5, 0.0, 1.0, 2.0,
        0.5, -0.5, -0.5, 0.0, 0.0, 2.0,
    };

    std::vector<unsigned int> indices{
        // Front
        0, 1, 2,
        2, 3, 0,

        // Back
        4, 5, 6,
        6, 7, 4,

        // Left
        8, 9, 10,
        10, 11, 8,

        // Right
        12, 13, 14,
        14, 15, 12,

        // Top
        16, 17, 18,
        18, 19, 16,

        // Bottom
        20, 21, 22,
        22, 23, 20,
    };

    mVertexArray = std::make_unique<VertexArray>();

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    mVertexBuffer = std::make_unique<VertexBuffer>(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(vertices[0])));
    mVertexArray->AddBuffer(*mVertexBuffer, layout);

    mIndexBuffer = std::make_unique<IndexBuffer>(indices.data(), static_cast<GLuint>(indices.size()));

    mTextureArray = Utils::LoadTextureArray(16, 16, {"res/images/grass_side.png", "res/images/grass_top.png", "res/images/dirt.png"});
}

void Renderer::Draw(int screenWidth, int screenHeight)
{
    mTheta += 0.01f;
    mTheta = fmod(mTheta, 360.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f * sin(mTheta), 2.0f, 2.0f * cos(mTheta)), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    float aspectRatio = static_cast<float>(screenWidth) / static_cast<float>(screenHeight);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShader->Bind();
    mShader->setMat4("view", view);
    mShader->setMat4("projection", projection);

    mVertexArray->Bind();
    mIndexBuffer->Bind();

    glDrawElements(GL_TRIANGLES, mIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
}