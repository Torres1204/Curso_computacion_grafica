//Ángel Joel Flores Torres
//Practica 7 
//08/10/2025
//318312857

#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other includes
#include "Shader.h"
#include "Camera.h"


// Function prototypes
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xPos, double yPos);
void DoMovement();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 5.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;

// Light attributes
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

// The MAIN function, from here we start the application and run the game loop
int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 7 Angel Flores", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;

	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	// OpenGL options
	glEnable(GL_DEPTH_TEST);

	// Build and compile our shader program
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

	// Textura: 707 x 353 píxeles
	// Cada cara: 118 píxeles de ancho, 353 de altoD
	// Proporción: 118/353 = 0.334
	// Centramos verticalmente: (1.0 - 0.334) / 2 = 0.333
	float vCenter = 0.5f;  // Centro vertical
	float vHeight = 0.167f;  // Mitad de la altura proporcional (0.334/2)
	float vMin = vCenter - vHeight;  // 0.333
	float vMax = vCenter + vHeight;  // 0.667

	GLfloat vertices[] =
	{
		// Positions            // Colors              // Texture Coords
		// Cara frontal - Número 1 del dado
		-0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      0.0f / 6.0f, vMax,
		 0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      1.0f / 6.0f, vMax,
		 0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      1.0f / 6.0f, vMin,
		-0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      0.0f / 6.0f, vMin,

		// Cara trasera - Número 6 del dado (opuesto al 1)
		 0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      5.0f / 6.0f, vMax,
		-0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      6.0f / 6.0f, vMax,
		-0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      6.0f / 6.0f, vMin,
		 0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      5.0f / 6.0f, vMin,

		 // Cara izquierda - Número 2 del dado
		 -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      1.0f / 6.0f, vMax,
		 -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      2.0f / 6.0f, vMax,
		 -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      2.0f / 6.0f, vMin,
		 -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      1.0f / 6.0f, vMin,

		 // Cara derecha - Número 5 del dado (opuesto al 2)
		  0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      4.0f / 6.0f, vMax,
		  0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      5.0f / 6.0f, vMax,
		  0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      5.0f / 6.0f, vMin,
		  0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      4.0f / 6.0f, vMin,

		  // Cara superior - Número 3 del dado
		  -0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      2.0f / 6.0f, vMax,
		   0.5f,  0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      3.0f / 6.0f, vMax,
		   0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      3.0f / 6.0f, vMin,
		  -0.5f,  0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      2.0f / 6.0f, vMin,

		  // Cara inferior - Número 4 del dado (opuesto al 3)
		  -0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      3.0f / 6.0f, vMin,
		   0.5f, -0.5f, -0.5f,    1.0f, 1.0f, 1.0f,      4.0f / 6.0f, vMin,
		   0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      4.0f / 6.0f, vMax,
		  -0.5f, -0.5f,  0.5f,    1.0f, 1.0f, 1.0f,      3.0f / 6.0f, vMax,
	};

	// Índices para las 6 caras del cubo
	GLuint indices[] =
	{
		// Cara frontal
		0, 1, 2,
		2, 3, 0,

		// Cara trasera
		4, 5, 6,
		6, 7, 4,

		// Cara izquierda
		8, 9, 10,
		10, 11, 8,

		// Cara derecha
		12, 13, 14,
		14, 15, 12,

		// Cara superior
		16, 17, 18,
		18, 19, 16,

		// Cara inferior
		20, 21, 22,
		22, 23, 20
	};

	// Set up buffers
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Texture Coordinate attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0);

	// Load texture
	GLuint texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	int textureWidth, textureHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* image = stbi_load("images/dado2.png", &textureWidth, &textureHeight, &nrChannels, 0);

	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(image);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		DoMovement();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lampShader.Use();

		// Camera transformations
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

		// Model transformation
		glm::mat4 model(1);

		// Get uniform locations
		GLint modelLoc = glGetUniformLocation(lampShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lampShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Bind texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		// Draw cube
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();

	return 0;
}

void DoMovement()
{
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);
	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}