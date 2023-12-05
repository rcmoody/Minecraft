#pragma once

#include <unordered_map>
#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "gl_object.hpp"

class Shader : public GLObject
{
public:
    Shader(const std::unordered_map<GLenum, std::string> &sources);
    ~Shader();
    Shader(Shader &&) = default;

    void Bind() const;
    void Unbind() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;
};