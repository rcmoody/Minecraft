#pragma once

#include <utility>

#include <spdlog/spdlog.h>
#include <glad/gl.h>

class GLObject
{
protected:
    GLuint mID;

public:
    explicit GLObject() = default;

    ~GLObject() = default;
 
    GLObject(const GLObject& other)
        : mID(other.mID) {}
 
    GLObject(GLObject&& other) noexcept
        : mID(std::exchange(other.mID, 0)) {}
 
    GLObject& operator=(const GLObject& other)
    {
        return *this = GLObject(other);
    }
 
    GLObject& operator=(GLObject&& other) noexcept
    {
        std::swap(mID, other.mID);
        return *this;
    }
};