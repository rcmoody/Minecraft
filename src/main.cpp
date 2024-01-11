#include <stdio.h>
#include <optional>

#include <spdlog/spdlog.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.hpp>

#include "debug.hpp"
#include "camera.hpp"
#include "renderer/renderer.hpp"
#include "world/world.hpp"

void FramebufferSizeCallback(GLFWwindow *window, int width, int height);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);

class Application
{
private:
    Application(GLFWwindow *window, float aspectRatio)
        : mWindow(window), mAspectRatio(aspectRatio), mCamera(Camera{.position = glm::vec3(-2.0f, 0.0f, -2.0f)}), mWorld(10, 10)
    {
        glfwSetWindowUserPointer(window, static_cast<void *>(this));
    }

public:
    GLFWwindow *mWindow;

    float mAspectRatio;

    Renderer mRenderer;
    Camera mCamera;
    World mWorld;

    static Application Init(const char *title, const char *windowIcon, int width, int height)
    {
        if (!glfwInit())
        {
            throw std::runtime_error("Failed to initialize GLFW.");
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWwindow *window = glfwCreateWindow(width, height, title, NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            throw std::runtime_error("Failed to create window.");
        }

        GLFWimage images[1];
        images[0].pixels = stbi_load(windowIcon, &images[0].width, &images[0].height, nullptr, STBI_rgb_alpha);
        glfwSetWindowIcon(window, 1, images);

        glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwSetCursorPosCallback(window, MouseCallback);

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

        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);

        return Application(window, aspectRatio);
    }

    void Run()
    {
        std::vector<Renderable> renderables;

        for (auto [position, chunk] : mWorld.chunks)
        {
            renderables.emplace_back(chunk.GenerateRenderable(mRenderer, glm::vec3(position.x * CHUNK_WIDTH, 0.0f, position.y * CHUNK_DEPTH)));
        }

        while (!glfwWindowShouldClose(mWindow))
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            static float lastFrame = currentFrame;
            float deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            mCamera.ProcessInput(mWindow, deltaTime);

            mRenderer.Draw(renderables, mCamera.getViewMatrix(), mCamera.getProjectionMatrix(mAspectRatio));

            glfwSwapBuffers(mWindow);

            glfwPollEvents();
        }
    }

    ~Application()
    {
        glfwTerminate();
    }
};

void FramebufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    auto app = static_cast<Application *>(glfwGetWindowUserPointer(window));
    app->mAspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos)
{
    auto app = static_cast<Application *>(glfwGetWindowUserPointer(window));

    if (app)
    {
        auto &camera = app->mCamera;

        static double lastX = xPos;
        static double lastY = yPos;

        float xOffset = static_cast<float>(xPos - lastX);
        float yOffset = static_cast<float>(lastY - yPos);

        xOffset *= camera.sensitivity;
        yOffset *= camera.sensitivity;

        camera.yaw += xOffset;
        camera.pitch += yOffset;

        camera.pitch = glm::clamp(camera.pitch, -89.9f, 89.9f);
        camera.yaw = std::fmod(camera.yaw, 360.0f);
        if (camera.yaw < 0.0f)
        {
            camera.yaw += 360.0f;
        }

        camera.UpdateFrontVector();

        lastX = xPos;
        lastY = yPos;
    }
}

int main(void)
{
#ifndef NDEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    try
    {
        Application app = Application::Init("Minecraft", "res/images/icon.png", 960, 540);
        app.Run();
    }
    catch (const std::exception &e)
    {
        spdlog::error(e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}