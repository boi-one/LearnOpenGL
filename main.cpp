#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "WarehouseEditor3D", 0, 0);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader shader("shader.vert", "shader.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		//kijk goed uit dat de positions niet omgedraaid staan, dan kan het namelijk zijn dat je niks ziet
		//position				//color
		0.45f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f, //rechts
		-0.45f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f, //links
		0.0f, 0.5f, 0.0f,		0.0f, 0.0f, 1.0f  //top
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	unsigned int EBO; //(Element Buffer Object) volgorde van hoe de vertices getekend moeten worden?
	unsigned int VAO; //(Vertex  Array  Object) volgorde van de vertex
	unsigned int VBO; //(Vertex  Buffer Object) lijst van de vertices
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//triangle 1
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //zet de actieve buffer naar de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //stuur de vertices naar de VBO	
	//set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.45f, 0.55f, 0.6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(2, &VAO);
	glDeleteBuffers(2, &VBO);

	glfwTerminate();
	return 0;
}