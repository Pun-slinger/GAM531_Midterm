#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"

void render(void);
void drawRectangle();
void testingFunc(float*);
void processInput(GLFWwindow* window);

unsigned int VBO, VBO1, VBO2, VBO3, VBO4;
unsigned int VAO, VAO1, VAO2, VAO3, VAO4;
unsigned int EBO, EBO1, EBO2, EBO3, EBO4;

int main() {

    // glfw: initialize 
    glfwInit();

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(1024, 768, "Two Objects", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

    Shader ourShader("shader.vs", "shader.fs"); 
    // Yellow 1 1 0
    // Blue 0 0 1
    // Red 1 0 0 
    // Pink 1 0 1
    // Green 1 1 1

    // first rectangle
    float vertices[] = {
        -0.61f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        -0.61f,  0.9f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -1.0f,  0.9f, 0.0f,  1.0f, 0.0f, 0.0f, // bottom left
        -1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, // top left 

    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	while (!glfwWindowShouldClose(window))
	{
        processInput(window);

        render();
        ourShader.use();
        // Draw 
        drawRectangle();
		glfwSwapBuffers(window);
		glfwPollEvents();
        testingFunc(vertices);
	}
	return 0;
}
//Render the background and clear the buffer
void render(void) {
	static const float bgcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, bgcolor);
}

void testingFunc(float* vertices) {
    //if (vertices[2] <= 1.0f) {
    //    for (int i = 0; i < 4; i++) {
    //        vertices[0] += 0.39;
    //    }
    //}
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Draw the fist Triangle
void drawRectangle() {
    //for (int i = 0; i < 24; i += 6) {
    //    vertices[i] += 0.39;
    //}
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// glfw: user input
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
