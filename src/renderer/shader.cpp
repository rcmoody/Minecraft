#include "shader.hpp"

#include <stdexcept>
#include <vector>
#include <utility>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::unordered_map<GLenum, std::string> &sources)
{
    mID = glCreateProgram();

    GLint success;
    GLchar infoLog[1024];

    std::vector<GLuint> shaders;
    for (auto &&[stage, source] : sources)
    {
        GLuint shader = shaders.emplace_back(glCreateShader(stage));

        const char *src = source.c_str();
        glShaderSource(shader, 1, &src, NULL);

        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            throw std::runtime_error("Failed to compile shader:\n" + std::string(infoLog));
        }

        glAttachShader(mID, shader);
    }

    glLinkProgram(mID);

    glGetProgramiv(mID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(mID, 1024, NULL, infoLog);
        throw std::runtime_error("Failed to link shader program:\n" + std::string(infoLog));
    }

    for (auto shader : shaders)
        glDeleteShader(shader);
}

Shader::Shader(Shader &&other)
    : mID(std::exchange(other.mID, 0)) {}

Shader &Shader::operator=(Shader &&other)
{
    std::swap(other, *this);
    return *this;
}

Shader::~Shader()
{
    glDeleteProgram(mID);
}

void Shader::Bind() const
{
    glUseProgram(mID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(mID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(mID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}