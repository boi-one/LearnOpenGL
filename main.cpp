#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* vertexShaderSource = R"(#version 330 core
			layout (location = 0) in vec3 aPos;
			void main()
			{
			   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
			})";

const char* fragmentShaderSource = R"(#version 330 core
			out vec4 FragColor;
			void main()
			{
				FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
			})";

const char* fragmentShaderSource2 = R"(#version 330 core
			out vec4 FragColor;
			void main()
			{
				FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
			})";

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

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, 0);
	glCompileShader(vertexShader);


	//opengl
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) //check for errors in the vertex shader
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, 0);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader2;
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, 0);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	unsigned int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);

	//check for errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	//delete the shaders bc they are now on the gpu
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(fragmentShader2);

	// set up vertex data (and buffer(s)) and configure vertex attributes
	float vertices[] = {
		-0.5f, 0.4f, 0.0f,
		-0.8f, -0.1f, 0.0f,
		-0.2f, -0.1f, 0.0f
	};

	float vertices2[] = {
		0.5f, 0.4f, 0.0f,
		0.8f, -0.1f, 0.0f,
		0.2f, -0.1f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2
	};

	unsigned int EBO; //(Element Buffer Object) volgorde van hoe de vertices getekend moeten worden?
	unsigned int VAO, VAO2; //(Vertex  Array  Object) volgorde van de vertex
	unsigned int VBO, VBO2; //(Vertex  Buffer Object) lijst van de vertices
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO);

	//triangle 1
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //zet de actieve buffer naar de VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //stuur de vertices naar de VBO	
	//set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//triangle 2
	glBindVertexArray(VAO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.45f, 0.55f, 0.6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUseProgram(shaderProgram2);

		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	glDeleteVertexArrays(2, &VAO);
	glDeleteBuffers(2, &VBO);
	glDeleteProgram(shaderProgram);
	glDeleteProgram(shaderProgram2);

	glfwTerminate();
	return 0;
}