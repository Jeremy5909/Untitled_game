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
{ //               COORDINATES                  /     COLORS           //
	-0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower left corner
	 0.5f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f, // Lower right corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f,     1.0f, 0.6f,  0.32f, // Upper corner
	-0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner left
	 0.25f, 0.5f * float(sqrt(3)) * 1 / 6, 0.0f,     0.9f, 0.45f, 0.17f, // Inner right
	 0.0f, -0.5f * float(sqrt(3)) * 1 / 3, 0.0f,     0.8f, 0.3f,  0.02f  // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1 // Upper triangle
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

    Shader shaderProgram("shaders/default.vert.glsl", "shaders/default.frag.glsl");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    // Position is layout 0 with 3 parts of type FLOAT that start every 6 floats and 0 offset
    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    // Position is layout 1 with 3 parts of type FLOAT that start every 6 floats and 3 floats offset
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

    glClearColor(0.2f,0.3f,0.3f,1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();
        // glUniform1f(uniID, 5f);
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
