#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

struct Camera
{
    float fov = 45.0f;
    float nearClip = 0.1f;
    float farClip = 100.0f;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

    float speed = 10.0f;
    float sensitivity = 0.1f;

    void processInput(GLFWwindow *window, float deltaTime)
    {
        float velocity = speed * deltaTime;

        glm::vec3 forward = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            position += forward * velocity;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            position -= forward * velocity;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            position -= glm::normalize(glm::cross(forward, up)) * velocity;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            position += glm::normalize(glm::cross(forward, up)) * velocity;
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            position += up * velocity;
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            position -= up * velocity;
    }

    glm::mat4 getViewMatrix() const
    {
        return glm::lookAt(position, position + front, up);
    }

    glm::mat4 getProjectionMatrix(float aspectRatio) const
    {
        return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
    }

    void setPitchAndYaw(float pitch, float yaw)
    {
        front = glm::normalize(glm::vec3{
            cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
            sin(glm::radians(pitch)),
            sin(glm::radians(yaw)) * cos(glm::radians(pitch))
        });
    }

    float getPitch() const
    {
        return glm::degrees(glm::asin(front.y));
    }

    float getYaw() const
    {
        return glm::degrees(glm::atan(front.z, front.x));
    }
};