#pragma once

#include <cstdint>
#include <cassert>
#include <array>
#include <vector>
#include <utility>

#include "../renderer/renderer.hpp"

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 256;
constexpr int CHUNK_DEPTH = 16;

constexpr int CHUNK_LOG2_WIDTH = 4;
constexpr int CHUNK_LOG2_HEIGHT = 8;
constexpr int CHUNK_LOG2_DEPTH = 4;

enum class VoxelType : uint8_t
{
    Air,
    Grass,
    Dirt,
    Stone,
};

class Voxel
{
public:
    VoxelType type;
};

class Chunk
{
public:
    std::array<Voxel, CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH> voxels;

    Chunk();

    Renderable GenerateRenderable(glm::vec3 position);

private:
    int getIndex(int x, int y, int z)
    {
        assert(x >= 0 && x < CHUNK_WIDTH && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_DEPTH);

        return x + (y << CHUNK_LOG2_WIDTH) + (z << (CHUNK_LOG2_WIDTH + CHUNK_LOG2_HEIGHT));
    }
};