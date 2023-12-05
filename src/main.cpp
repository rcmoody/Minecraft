#include <stdio.h>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.hpp>

#include "debug.hpp"
#include "renderer/renderer.hpp"

constexpr char WINDOW_TITLE[] = "Minecraft";
constexpr char WINDOW_ICON_PATH[] = "res/images/icon.png";
constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 540;

int screenWidth = WINDOW_WIDTH;
int screenHeight = WINDOW_HEIGHT;

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    screenWidth = width;
    screenHeight = height;
}

void Setup()
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw std::runtime_error("Failed to create window.");
    }

    GLFWimage images[1];
    images[0].pixels = stbi_load(WINDOW_ICON_PATH, &images[0].width, &images[0].height, nullptr, STBI_rgb_alpha);
    glfwSetWindowIcon(window, 1, images);

    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    glfwMakeContextCurrent(window);

    int version = gladLoadGL(glfwGetProcAddress);
    if (version == 0)
    {
        throw std::runtime_error("Failed to initialize GLAD.");
    }

#ifndef NDEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(Debug::DebugCallback, 0);
#endif

    Renderer renderer;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Draw(screenWidth, screenHeight);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
}

int main(void)
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try
    {
        Setup();
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
        return -1;
    }

    return 0;
}