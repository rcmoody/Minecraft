#include "chunk.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../utils.hpp"

Chunk::Chunk()
{
    for (int x = 0; x < CHUNK_WIDTH; ++x)
    {
        for (int y = 0; y < CHUNK_HEIGHT; ++y)
        {
            for (int z = 0; z < CHUNK_DEPTH; ++z)
            {
                VoxelType type;

                if (y > 50)
                {
                    type = VoxelType::Air;
                }
                else if (y == 50)
                {
                    type = VoxelType::Grass;
                }
                else if (y >= 45)
                {
                    type = VoxelType::Dirt;
                }
                else
                {
                    type = VoxelType::Stone;
                }

                int index = getIndex(x, y, z);
                voxels[index] = Voxel{type};
            }
        }
    }
}

Renderable Chunk::GenerateRenderable(glm::vec3 position)
{
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = Utils::ReadFile("res/shaders/vert.glsl");
    sources[GL_FRAGMENT_SHADER] = Utils::ReadFile("res/shaders/frag.glsl");
    Shader shader(sources);

    // clang-format off
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
    // clang-format on

    VertexArray vertexArray;

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(3);

    VertexBuffer vertexBuffer(vertices.data(), static_cast<GLsizeiptr>(vertices.size() * sizeof(vertices[0])));
    vertexArray.AddBuffer(vertexBuffer, layout);

    IndexBuffer indexBuffer(indices.data(), static_cast<GLuint>(indices.size()));

    TextureArray textureArray = Utils::LoadTextureArray(16, 16, {"res/images/grass_side.png", "res/images/grass_top.png", "res/images/dirt.png"});

    Mesh mesh{
        std::move(vertexArray),
        std::move(vertexBuffer),
        std::move(indexBuffer),
        std::move(textureArray),
        std::move(shader),
    };

    return {
        std::move(mesh),
        glm::translate(glm::mat4(1.0f), position),
    };
}