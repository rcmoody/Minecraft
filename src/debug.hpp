#ifndef NDEBUG

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <glad/gl.h>

namespace Debug
{
    auto OpenGLLogger = spdlog::stdout_color_mt("OpenGL");

    spdlog::level::level_enum ConvertDebugTypeToLogLevel(GLenum debugType)
    {
        switch (debugType)
        {
        case GL_DEBUG_TYPE_ERROR:
            return spdlog::level::err;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return spdlog::level::warn;
        case GL_DEBUG_TYPE_PORTABILITY:
        case GL_DEBUG_TYPE_PERFORMANCE:
            return spdlog::level::info;
        case GL_DEBUG_TYPE_MARKER:
        case GL_DEBUG_TYPE_PUSH_GROUP:
        case GL_DEBUG_TYPE_POP_GROUP:
            return spdlog::level::trace;
        default:
            return spdlog::level::debug;
        }
    }

    std::string GetDebugSourceString(GLenum source)
    {
        switch (source)
        {
        case GL_DEBUG_SOURCE_API:
            return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION:
            return "Application";
        case GL_DEBUG_SOURCE_OTHER:
            return "Other";
        default:
            return "Unknown";
        }
    }

    std::string GetDebugTypeString(GLenum type)
    {
        switch (type)
        {
        case GL_DEBUG_TYPE_ERROR:
            return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY:
            return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE:
            return "Performance";
        case GL_DEBUG_TYPE_MARKER:
            return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP:
            return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP:
            return "Pop Group";
        case GL_DEBUG_TYPE_OTHER:
            return "Other";
        default:
            return "Unknown";
        }
    }

    std::string GetDebugSeverityString(GLenum severity)
    {
        switch (severity)
        {
        case GL_DEBUG_SEVERITY_HIGH:
            return "High";
        case GL_DEBUG_SEVERITY_MEDIUM:
            return "Medium";
        case GL_DEBUG_SEVERITY_LOW:
            return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "Notification";
        default:
            return "Unknown";
        }
    }

    void GLAPIENTRY DebugCallback(GLenum source,
                                  GLenum type,
                                  GLuint id,
                                  GLenum severity,
                                  GLsizei length,
                                  const GLchar *message,
                                  const void *userParam)
    {
        auto logLevel = ConvertDebugTypeToLogLevel(type);
        std::string sourceStr = GetDebugSourceString(source);
        std::string typeStr = GetDebugTypeString(type);
        std::string severityStr = GetDebugSeverityString(severity);

        OpenGLLogger->log(logLevel, "[Source: {}, Type: {}, Severity: {}]: {}", sourceStr, typeStr, severityStr, message);
    }
}

#endif