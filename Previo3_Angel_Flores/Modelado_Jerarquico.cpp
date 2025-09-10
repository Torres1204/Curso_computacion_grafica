//Ángel Joel Flores Torres
//Practica 5
//10/09/2025
//318312857

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);

const GLint WIDTH = 1200, HEIGHT = 800;

//For Keyboard
float	movX = 0.0f,
movY = 0.0f,
movZ = -5.0f,
rot = 0.0f;

//For model
float	hombro = 0.0f,
codo = 0.0f,
muneca = 0.0f,
dedo1_1 = 0.0f,
dedo1_2 = 0.0f,
dedo1_3 = 0.0f,
dedo1_4 = 0.0f,
dedo1_5 = 0.0f,
dedo2_1 = 0.0f,
dedo2_2 = 0.0f,
dedo2_3 = 0.0f,
dedo2_4 = 0.0f,
dedo2_5 = 0.0f,

int main() {
	glfwInit();
	//Verificación de compatibilidad 
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 5 Angel Flores", nullptr, nullptr);

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
	// use with Orthographic Projection

	// use with Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 
		0.5f, -0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		0.5f,  0.5f, 0.5f,  
		-0.5f,  0.5f, 0.5f, 
		-0.5f, -0.5f, 0.5f, 
		
	    -0.5f, -0.5f,-0.5f, 
		 0.5f, -0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
		 0.5f,  0.5f,-0.5f, 
	    -0.5f,  0.5f,-0.5f, 
	    -0.5f, -0.5f,-0.5f, 
		
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  -0.5f, 0.5f,
      
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f, 
		0.5f, -0.5f,  0.5f, 
		0.5f, -0.5f,  0.5f, 
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,
		
		-0.5f,  0.5f, -0.5f,
		0.5f,  0.5f, -0.5f, 
		0.5f,  0.5f,  0.5f, 
		0.5f,  0.5f,  0.5f, 
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
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
	

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar
	glm::vec3 color= glm::vec3(0.0f, 0.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp
		glm::mat4 modelTemp2 = glm::mat4(1.0f); //Temp

		//View set up 
		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		GLint uniformColor = ourShader.uniformColor;

		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
	
		glBindVertexArray(VAO);
		
		//Modelo Bicep 
		model = glm::rotate(model, glm::radians(hombro), glm::vec3(0.0f, 0.0, 1.0f)); //hombro
		modelTemp = model = glm::translate(model, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(3.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.73f, 0.75f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//A

		//Modelo Antebrazo
		model = glm::translate(modelTemp, glm::vec3(1.5f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(codo), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTemp = model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(2.0f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//B

		//Modelo Palma
		model = glm::translate(modelTemp, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(muneca), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp2 = modelTemp = model = glm::translate(model, glm::vec3(0.25f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.0f, 1.0f));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);//C

		const glm::vec3 ESC_FALANGE = glm::vec3(0.85f, 0.24f, 0.14f);
		const float HALF_X = 0.425f; // centro de la falange (mitad de X)

		// PULGAR 
		modelTemp = modelTemp2;
		// Falange 1
		model = glm::translate(modelTemp, glm::vec3(0.10f, 0.12f, 0.30f));          
		model = glm::rotate(model, glm::radians(-40.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
		model = glm::rotate(model, glm::radians(dedo1_1), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(0.0f, 1.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange 2
		model = glm::translate(modelTemp, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2_1), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(1.0f, 0.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ÍNDICE 
		modelTemp = modelTemp2;
		// Falange 1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.32f));
		model = glm::rotate(model, glm::radians(dedo1_2), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(0.0f, 1.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange 2
		model = glm::translate(modelTemp, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2_2), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(1.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// MEDIO 
		modelTemp = modelTemp2;
		// Falange 1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, 0.12f));
		model = glm::rotate(model, glm::radians(dedo1_3), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(0.0f, 1.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange 2
		model = glm::translate(modelTemp, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2_3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(1.0f, 0.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// ANULAR 
		modelTemp = modelTemp2;
		// Falange 1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, -0.12f));
		model = glm::rotate(model, glm::radians(dedo1_4), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(0.0f, 1.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Falange 2
		model = glm::translate(modelTemp, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2_4), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(1.0f, 0.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// MEÑIQUE 
		modelTemp = modelTemp2;
		// Falange 1
		model = glm::translate(modelTemp, glm::vec3(0.25f, 0.35f, -0.32f));
		model = glm::rotate(model, glm::radians(dedo1_5), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTemp = model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(0.0f, 1.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model)); 
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Falange 2
		model = glm::translate(modelTemp, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(dedo2_5), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3(HALF_X, 0.0f, 0.0f));
		model = glm::scale(model, ESC_FALANGE);
		color = glm::vec3(1.0f, 0.0f, 1.0f); 
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
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

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.08f;
	 if (glfwGetKey(window,GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.08f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.18f;

	 // Hombro
	 if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		 hombro += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		 hombro -= 0.18f;
	 if (hombro > 90.0f) hombro = 90.0f;
	 if (hombro < -90.0f) hombro = -90.0f;

	 // Codo
	 if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		 codo += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
		 codo -= 0.18f;
	 if (codo > 0.0f) codo = 0.0f;
	 if (codo < -90.0f) codo = -90.0f;

	 // Muñeca
	 if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		 muneca += 0.18f;
	 if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
		 muneca -= 0.18f;
	 if (muneca > 90.0f) muneca = 90.0f;
	 if (muneca < -90.0f) muneca = -90.0f;

	 //Primeras falanges
	 // J y U mueven todas las primeras falanges
	 if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
		 dedo1_1 += 0.18f; 
		 dedo1_2 += 0.18f; 
		 dedo1_3 += 0.18f; 
		 dedo1_4 += 0.18f; 
		 dedo1_5 += 0.18f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		 dedo1_1 -= 0.18f; 
		 dedo1_2 -= 0.18f; 
		 dedo1_3 -= 0.18f; 
		 dedo1_4 -= 0.18f; 
		 dedo1_5 -= 0.18f;
	 }
	 if (dedo1_1 > 6.0f)  dedo1_1 = 6.0f;   
	 if (dedo1_1 < -12.0f) dedo1_1 = -12.0f;
	 if (dedo1_2 > 6.0f)  dedo1_2 = 6.0f;   
	 if (dedo1_2 < -12.0f) dedo1_2 = -12.0f;
	 if (dedo1_3 > 6.0f)  dedo1_3 = 6.0f;   
	 if (dedo1_3 < -12.0f) dedo1_3 = -12.0f;
	 if (dedo1_4 > 6.0f)  dedo1_4 = 6.0f;   
	 if (dedo1_4 < -12.0f) dedo1_4 = -12.0f;
	 if (dedo1_5 > 6.0f)  dedo1_5 = 6.0f;   
	 if (dedo1_5 < -12.0f) dedo1_5 = -12.0f;

	 //Segundas falanges
	 // K y I mueven todas las segundas falanges
	 if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
		 dedo2_1 += 0.18f; dedo2_2 += 0.18f; dedo2_3 += 0.18f; dedo2_4 += 0.18f; dedo2_5 += 0.18f;
	 }
	 if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
		 dedo2_1 -= 0.18f; dedo2_2 -= 0.18f; dedo2_3 -= 0.18f; dedo2_4 -= 0.18f; dedo2_5 -= 0.18f;
	 }
	 if (dedo2_1 > 0.0f) dedo2_1 = 0.0f;  
	 if (dedo2_1 < -105.0f) dedo2_1 = -105.0f;
	 if (dedo2_2 > 0.0f) dedo2_2 = 0.0f;  
	 if (dedo2_2 < -105.0f) dedo2_2 = -105.0f;
	 if (dedo2_3 > 0.0f) dedo2_3 = 0.0f;  
	 if (dedo2_3 < -105.0f) dedo2_3 = -105.0f;
	 if (dedo2_4 > 0.0f) dedo2_4 = 0.0f;  
	 if (dedo2_4 < -105.0f) dedo2_4 = -105.0f;
	 if (dedo2_5 > 0.0f) dedo2_5 = 0.0f;  
	 if (dedo2_5 < -105.0f) dedo2_5 = -105.0f;
 }

