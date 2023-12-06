#include <stdio.h>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.hpp>

#include "debug.hpp"
#include "camera.hpp"
#include "renderer/renderer.hpp"
#include "world/world.hpp"

#define ASPECT_RATIO(WIDTH, HEIGHT) static_cast<float>(WIDTH) / static_cast<float>(HEIGHT)

constexpr char WINDOW_TITLE[] = "Minecraft";
constexpr char WINDOW_ICON_PATH[] = "res/images/icon.png";
constexpr int WINDOW_WIDTH = 960;
constexpr int WINDOW_HEIGHT = 540;

float aspectRatio = ASPECT_RATIO(WINDOW_WIDTH, WINDOW_HEIGHT);

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    aspectRatio = ASPECT_RATIO(width, height);
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    Camera *camera = static_cast<Camera *>(glfwGetWindowUserPointer(window));

    if (camera)
    {
        static double lastX = xPos;
        static double lastY = yPos;
        static float pitch = camera->getPitch();
        static float yaw = camera->getYaw();

        float xOffset = static_cast<float>(xPos - lastX);
        float yOffset = static_cast<float>(lastY - yPos);

        xOffset *= camera->sensitivity;
        yOffset *= camera->sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        pitch = glm::clamp(pitch, -89.9f, 89.9f);
        yaw = std::fmod(yaw, 360.0f);
        if (yaw < 0.0f)
        {
            yaw += 360.0f;
        }

        camera->setPitchAndYaw(pitch, yaw);

        lastX = xPos;
        lastY = yPos;
    }
}

void Run()
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

    Camera camera{
        .position = glm::vec3(0.0f, 0.0f, -2.0f),
    };

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetWindowUserPointer(window, static_cast<void *>(&camera));

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

    World world(10, 10);

    Renderer renderer;

    for (auto [position, chunk] : world.chunks)
    {
        renderer.mRenderables.emplace_back(chunk.GenerateRenderable(glm::vec3(position.x * CHUNK_WIDTH, 0.0f, position.y * CHUNK_DEPTH)));
    }

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        static float lastFrame = currentFrame;
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        camera.processInput(window, deltaTime);

        renderer.Draw(camera.getViewMatrix(), camera.getProjectionMatrix(aspectRatio));

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
        Run();
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}