cmake_minimum_required(VERSION 3.30)
project(untitled_game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/shaderClass.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/Texture.cpp
    src/Camera.cpp
    src/Mesh.cpp

    src/glad.c
    src/stb.cpp
)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)

file(COPY ${CMAKE_SOURCE_DIR}/Shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Textures DESTINATION ${CMAKE_BINARY_DIR})
