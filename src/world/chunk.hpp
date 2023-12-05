#pragma once

#include <cstdint>
#include <cassert>
#include <array>
#include <vector>
#include <utility>

constexpr int CHUNK_WIDTH = 16;
constexpr int CHUNK_HEIGHT = 255;
constexpr int CHUNK_DEPTH = 16;

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

private:
    int GetIndex(int x, int y, int z)
    {
        assert(x >= 0 && x < CHUNK_WIDTH && y >= 0 && y < CHUNK_HEIGHT && z >= 0 && z < CHUNK_DEPTH);

        return x + CHUNK_WIDTH * (y + CHUNK_HEIGHT * z);
    }
};