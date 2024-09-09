cmake_minimum_required(VERSION 3.30)
project(minecraft)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(include shaders)

add_executable(
    ${PROJECT_NAME}
    src/main.cpp
    src/shaderClass.cpp
    src/VAO.cpp
    src/VBO.cpp
    src/EBO.cpp
    src/glad.c
)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR})
