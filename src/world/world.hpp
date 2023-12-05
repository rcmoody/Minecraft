#pragma once

#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "chunk.hpp"

class World
{
public:
    std::unordered_map<glm::ivec2, Chunk> chunks;

    World(int width, int height);
};