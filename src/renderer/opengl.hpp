#pragma once

#include <utility>

#include <spdlog/spdlog.h>
#include <glad/gl.h>

class OpenGLObject
{
protected:
    GLuint mID;

public:
    explicit OpenGLObject() = default;
    ~OpenGLObject() = default;

    OpenGLObject(OpenGLObject &&other) noexcept
        : mID(std::exchange(other.mID, 0)) {}
    OpenGLObject &operator=(OpenGLObject &&other) noexcept
    {
        std::swap(mID, other.mID);
        return *this;
    }

    OpenGLObject(const OpenGLObject &) = delete;
    OpenGLObject &operator=(const OpenGLObject &) = delete;
};