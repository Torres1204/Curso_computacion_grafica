//Ángel Joel Flores Torres
//Practica 4
//05/09/2025
//318312857

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow* window);

const GLint WIDTH = 800, HEIGHT = 600;
//Manipulación de cámara sin tener que volver a compilar
float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);*/

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 4 Angel Flores", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	//Información de la GPU
	std::cout << "> Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "> Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "> Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "> SL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");

	// Set up vertex data (and buffer(s)) and attribute pointers

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,//Front
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,

		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,//Back
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		-0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,

		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,

		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	//projection = glm::ortho(0.0f, (GLfloat)screenWidth, 0.0f, (GLfloat)screenHeight, 0.1f, 1000.0f);//Izq,Der,Fondo,Alto,Cercania,Lejania
	while (!glfwWindowShouldClose(window))
	{
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.7f, 0.85f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		view = glm::translate(view, glm::vec3(movX, movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);

		// GATO
		// Función para cambiar el color de todos los vértices
		auto setColor = [&](float r, float g, float b) {
			float coloredVertices[36 * 6];
			for (int i = 0; i < 36; ++i) {
				coloredVertices[i * 6 + 0] = vertices[i * 6 + 0];
				coloredVertices[i * 6 + 1] = vertices[i * 6 + 1];
				coloredVertices[i * 6 + 2] = vertices[i * 6 + 2];
				coloredVertices[i * 6 + 3] = r;
				coloredVertices[i * 6 + 4] = g;
				coloredVertices[i * 6 + 5] = b;
			}
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(coloredVertices), coloredVertices, GL_STATIC_DRAW);
			};

		// Cuerpo principal (gris claro) 
		setColor(0.6f, 0.6f, 0.6f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.6f, 2.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Blanco en el vientre (costados)
		setColor(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.054f, -0.0f));
		model = glm::scale(model, glm::vec3(-2.01f, 0.11f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Blanco en el vientre (frente y atras)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.00f, 0.11f, -0.00f));
		model = glm::scale(model, glm::vec3(0.80f, 0.22f, 2.01f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja izquierda (gris claro)
		setColor(0.6f, 0.6f, 0.6f); 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, 1.775f, 0.85f));
		model = glm::scale(model, glm::vec3(-0.60f, 0.35f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja derecha (gris claro)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, 1.775f, 0.85f));
		model = glm::scale(model, glm::vec3(0.60f, 0.35f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja izquierda interna (gris oscuro)
		setColor(0.5f, 0.5f, 0.5f); 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, 1.73f, 0.86f));
		model = glm::scale(model, glm::vec3(-0.30f, 0.25f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Oreja derecha interna (gris oscuro)
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, 1.73f, 0.86f));
		model = glm::scale(model, glm::vec3(0.30f, 0.25f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas delanteras parte superior (gris claro)
		// Pata frontal izquierda
		setColor(0.6f, 0.6f, 0.6f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, -0.055f, 0.7f));
		model = glm::scale(model, glm::vec3(-0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pata frontal derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, -0.055f, 0.7f));
		model = glm::scale(model, glm::vec3(0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas traseras parte superior (gris claro)
		// Pata trasera izquierda 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, -0.055f, -0.7f));
		model = glm::scale(model, glm::vec3(-0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pata trasera derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, -0.055f, -0.7f));
		model = glm::scale(model, glm::vec3(0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas delanteras parte inferior (gris oscuro)
		// Pata frontal izquierda 
		setColor(0.5f, 0.5f, 0.5f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, -0.16f, 0.7f));
		model = glm::scale(model, glm::vec3(-0.60f, 0.11f, -0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pata frontal derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, -0.16f, 0.7f));
		model = glm::scale(model, glm::vec3(0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Patas traseras parte inferior (gris oscuro)
		// Pata trasera izquierda 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.70f, -0.16f, -0.7f));
		model = glm::scale(model, glm::vec3(-0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pata trasera derecha 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.70f, -0.16f, -0.7f));
		model = glm::scale(model, glm::vec3(0.60f, 0.11f, 0.6f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Ojos (verde)
		// Iris izquierdo
		setColor(0.10f, 0.80f, 0.15f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.46f, 1.06f, 1.00010f)); 
		model = glm::scale(model, glm::vec3(0.36f, 0.44f, 0.00040f));      
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Iris derecho
		setColor(0.10f, 0.80f, 0.15f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.46f, 1.06f, 1.00010f));
		model = glm::scale(model, glm::vec3(0.36f, 0.44f, 0.00040f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pupila izquierda (negro)
		setColor(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.40f, 1.13f, 1.00200f));  
		model = glm::scale(model, glm::vec3(0.24f, 0.30f, 0.00030f));       
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pupila derecha (negro)
		setColor(0.0f, 0.0f, 0.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.52f, 1.13f, 1.00200f));
		model = glm::scale(model, glm::vec3(0.24f, 0.30f, 0.00030f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brillo izquierdo (blanco)
		setColor(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.32f, 1.23f, 1.00400f));  
		model = glm::scale(model, glm::vec3(0.08f, 0.10f, 0.00020f));       
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Brillo derecho (blanco)
		setColor(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.60f, 1.23f, 1.00400f));
		model = glm::scale(model, glm::vec3(0.08f, 0.10f, 0.00020f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Hocico (blanco) 
		setColor(1.0f, 1.0f, 1.0f);
		// Parte superior 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.66f, 1.045f));
		model = glm::scale(model, glm::vec3(0.62f, 0.26f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pierna inferior izquierda 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.195f, 0.52f, 1.045f));
		model = glm::scale(model, glm::vec3(0.23f, 0.14f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Pierna inferior derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.195f, 0.52f, 1.045f));
		model = glm::scale(model, glm::vec3(0.23f, 0.14f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Nariz (rosa) 
		setColor(1.0f, 0.73f, 0.75f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.735f, 1.055f)); 
		model = glm::scale(model, glm::vec3(0.22f, 0.11f, 0.081f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Bigotes (blanco)
		// Bigotes izquierdos
		setColor(1.0f, 1.0f, 1.0f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.11f, 0.74f, 0.82f)); 
		model = glm::scale(model, glm::vec3(0.22f, 0.10f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.11f, 0.56f, 0.82f));
		model = glm::scale(model, glm::vec3(0.22f, 0.10f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Bigotes derechos
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.11f, 0.74f, 0.82f)); 
		model = glm::scale(model, glm::vec3(0.22f, 0.10f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.11f, 0.56f, 0.82f)); 
		model = glm::scale(model, glm::vec3(0.22f, 0.10f, 0.10f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Cola (gris oscuro) 
		// Parte base, pegada al cuerpo
		setColor(0.33f, 0.33f, 0.35f);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.28f, -1.08f)); // sube para que sobrepase el techo
		model = glm::scale(model, glm::vec3(0.34f, 1.70f, -0.30f));  // X más ancho, Y más alto, Z mismo grosor
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Parte superior 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.28f, -0.790f)); // CENTRO TRAMO (encima sin hueco)
		model = glm::scale(model, glm::vec3(0.34f, 0.30f, 0.88f));  // ancho X, alto Y, largo hacia +Z
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);

	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

void Inputs(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		movX += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		movX -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		movY += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		movY -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		movZ -= 0.08f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		movZ += 0.08f;
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		rot += 0.4f;
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		rot -= 0.4f;
}