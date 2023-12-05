cmake_minimum_required(VERSION 3.5)

project(Minecraft)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(deps/glfw)
add_subdirectory(deps/glad)
add_subdirectory(deps/glm)
add_subdirectory(deps/spdlog)

add_executable(Minecraft
    src/main.cpp
    src/debug.hpp
    src/utils.hpp
    src/camera.hpp
    src/world/chunk.cpp
    src/world/chunk.hpp
    src/world/world.cpp
    src/world/world.hpp
    src/renderer/renderer.cpp
    src/renderer/renderer.hpp
    src/renderer/opengl.hpp
    src/renderer/shader.cpp
    src/renderer/shader.cpp
    src/renderer/shader.hpp
    src/renderer/vertex_array.cpp
    src/renderer/vertex_array.hpp
    src/renderer/vertex_buffer_layout.cpp
    src/renderer/vertex_buffer_layout.hpp
    src/renderer/buffer.cpp
    src/renderer/buffer.hpp
    src/renderer/vertex_buffer.cpp
    src/renderer/vertex_buffer.hpp
    src/renderer/index_buffer.cpp
    src/renderer/index_buffer.hpp
    src/renderer/texture.cpp
    src/renderer/texture.hpp
    src/renderer/texture_array.cpp
    src/renderer/texture_array.hpp

    deps/stb/stb_image.cpp
    deps/stb/stb_image.hpp
)

target_include_directories(Minecraft PRIVATE deps/glfw/include)
target_include_directories(Minecraft PRIVATE deps/glad/include)
target_include_directories(Minecraft PRIVATE deps/spdlog/include)
target_include_directories(Minecraft PRIVATE deps/stb)

target_link_libraries(Minecraft PRIVATE glfw glad glm spdlog)

add_custom_target(
    copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/res
    $<TARGET_FILE_DIR:Minecraft>/res
    COMMENT "Copying resources into binary directory"
)