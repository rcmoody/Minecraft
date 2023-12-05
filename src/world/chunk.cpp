#include "chunk.hpp"

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

                int index = GetIndex(x, y, z);
                voxels[index] = Voxel{type};
            }
        }
    }
}