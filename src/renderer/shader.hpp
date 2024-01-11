#pragma once

#include <unordered_map>
#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "opengl.hpp"

struct ShaderDeleter
{
    void operator()(GLuint id)
    {
        glDeleteProgram(id);
    }
};

class Shader : public OpenGLObject<ShaderDeleter>
{
public:
    Shader(const std::unordered_map<GLenum, std::string> &sources);

    void Bind() const;
    void Unbind() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};