#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


// Vertices coordinates
GLfloat vertices[] =
{
    -.5f,-.5f,0.0f,
    -.5f,.5f,0.0f,
    .5f,.5f,0.0f,
    .5f,-.5f,0.0f,
};

// Indices for vertices order
GLuint indices[] =
{
    0,1,2,
    0,3,2
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    GLFWwindow* window = glfwCreateWindow(800, 800, "Minecraft", NULL, NULL);

    // Failed to create GLFW window
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("shaders/default.vert", "shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        // Check for events
        glfwPollEvents();
    }
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}
