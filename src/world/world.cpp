#include "world.hpp"

World::World(int width, int height)
{
    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            glm::ivec2 pos = glm::ivec2(x, y);
            chunks[pos] = Chunk();
        }
    }
}