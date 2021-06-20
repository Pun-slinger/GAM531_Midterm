#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/gtc/type_ptr.hpp>

#include <iostream>

#include "shader.h"

void render(void);
void drawRectangle();
void drawRectangle1();
void drawRectangle2();
void drawRectangle3();
void drawRectangle4();
void drawRectangle5();
void bind(GLuint&, GLuint&, GLuint&, float, float r = 0.0f, float g = 0.0f, float b = 0.0f);

// Bricks
GLuint VBO, VBO1, VBO2, VBO3, VBO4, VBO5;
GLuint VAO, VAO1, VAO2, VAO3, VAO4, VAO5;
GLuint EBO, EBO1, EBO2, EBO3, EBO4, EBO5;

// Platform



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
    // Red 1 0 0 
    // Yellow 1 1 0
    // Blue 0 0 1
    // Pink 1 0 1
    // Green 1 1 1


    bind(VAO, VBO, EBO, 1.0f, 1.0f);
    bind(VAO1, VBO1, EBO1, 0.88f, 1.0f, 1.0f);
    bind(VAO2, VBO2, EBO2, 0.76f, 1.0f, 0.5f, 0.0f);
    bind(VAO3, VBO3, EBO3, 0.64f, 1.0f, 0.0f, 1.0f);
    bind(VAO4, VBO4, EBO4, 0.52f, 0.0f, 1.0f, 0.0f);
    bind(VAO5, VBO5, EBO5, 0.40f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
        render();
        ourShader.use();
        // Draw 

        glm::mat4 transform = glm::mat4(1.0f);
        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        drawRectangle();
        drawRectangle1();
        drawRectangle2();
        drawRectangle3();
        drawRectangle4();
        drawRectangle5();

        for (int i = 0; i < 8; i++) {
            transform = glm::translate(transform, glm::vec3(0.25f, 0.0f, 0.0f));
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
            drawRectangle();
            drawRectangle1();
            drawRectangle2();
            drawRectangle3();
            drawRectangle4();
            drawRectangle5();
        }

        // Draw second rectangle
        //glm::mat4 transform1 = glm::mat4(1.0f);
        //unsigned int transformLoc1 = glGetUniformLocation(ourShader.ID, "transform");
        //glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(transform1));
        //drawRectangle1();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
//Render the background and clear the buffer
void render(void) {
	static const float bgcolor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	glClearBufferfv(GL_COLOR, 0, bgcolor);
}

void bind(GLuint& A, GLuint& B, GLuint& E, float y, float r, float g, float b) {
    float vertices[] = {
    -0.76f,  y, 0.0f, r, g, b, // top right
    -0.76f,  y - 0.1, 0.0f, r, g, b, // bottom right
    -0.989f,  y - 0.1, 0.0f,  r, g, b, // bottom left
    -0.989f,  y, 0.0f,  r, g, b, // top left 

    };
    unsigned int indices[] = {
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    glGenVertexArrays(1, &A);
    glGenBuffers(1, &B);
    glGenBuffers(1, &E);
    glBindVertexArray(A);

    glBindBuffer(GL_ARRAY_BUFFER, B);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, E);
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
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectangle1() {
    glBindVertexArray(VAO1);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectangle2() {
    glBindVertexArray(VAO2);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectangle3() {
    glBindVertexArray(VAO3);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectangle4() {
    glBindVertexArray(VAO4);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void drawRectangle5() {
    glBindVertexArray(VAO5);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
