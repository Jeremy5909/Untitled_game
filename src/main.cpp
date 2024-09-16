#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_projection.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include "shaderClass.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ //    COORDINATES       /      COLORS           TEXTURE 
    -0.5f, 0.0f,  0.5f,     0.83f,  0.70f, 0.44f,   0.0f, 0.0f,
    -0.5f, 0.0f, -0.5f,     0.83f,  0.70f, 0.44f,   5.0f, 0.0f,
     0.5f, 0.0f, -0.5f,     0.83f,  0.70f, 0.44f,   0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,     0.83f,  0.70f, 0.44f,   5.0f, 0.0f,
     0.0f, 0.8f,  0.0f,     0.92f,  0.86f, 0.76f,   2.5f, 5.0f,
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 1, 4,
    1, 2, 4,
    2, 3, 4,
    3, 0, 4,
};

void fix_mac_render(GLFWwindow* window) {
#ifdef __APPLE__
    static bool macMoved = false;

    if(!macMoved) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMoved = true;
    }
#endif
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    GLFWwindow* window = glfwCreateWindow(width, height, "untitled_game", NULL, NULL);

    // Failed to create GLFW window
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, width, height);

    Shader shaderProgram("Shaders/default.vert.glsl", "Shaders/default.frag.glsl");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Position is layout 0 with 3 parts of type FLOAT that start every 8 floats and 0 offset
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    // Position is layout 1 with 3 parts of type FLOAT that start every 8 floats and 3 floats offset
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // Position is layout 2 with 2 parts of type FLOAT that start every 8 floats and 6 floats offset
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();


    // Texture
    
    Texture dirt("Textures/Dirt.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    dirt.texUnit(shaderProgram, "tex0", 0);

    glClearColor(0.2f,0.3f,0.3f,1.0f);

    glEnable(GL_DEPTH_TEST);

    Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Inputs(window);
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

        dirt.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        fix_mac_render(window);

        // Check for events
        glfwPollEvents();
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    dirt.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
