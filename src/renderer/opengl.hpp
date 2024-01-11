#pragma once

#include <utility>

#include <spdlog/spdlog.h>
#include <glad/gl.h>

template <typename DeleterFn>
class OpenGLObject
{
protected:
    GLuint mID;

public:
    OpenGLObject() = default;
    
    ~OpenGLObject()
    {
        DeleterFn(mID);
    }

    OpenGLObject(const OpenGLObject &) = delete;
    OpenGLObject &operator=(const OpenGLObject &) = delete;

    OpenGLObject(OpenGLObject &&other)
        : mID(std::exchange(other.mID, 0)) {}

    OpenGLObject &operator=(OpenGLObject &&other)
    {
        std::swap(mID, other.mID);
        return *this;
    }
};