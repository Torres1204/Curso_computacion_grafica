//�ngel Joel Flores Torres
//Practica 6
//25/09/2025
//318312857

// Std. Includes
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"

// Properties
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Function prototypes
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode );
void MouseCallback( GLFWwindow *window, double xPos, double yPos );
void DoMovement( );

// Camera
Camera camera( glm::vec3( 0.0f, 0.0f, 3.0f ) );
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main( )
{
    // Init GLFW
    glfwInit( );
    // Set all the required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
    
    // Create a GLFWwindow object that we can use for GLFW's functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Practica 6 Angel Flores", nullptr, nullptr );
    
    if ( nullptr == window )
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate( );
        
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent( window );
    
    glfwGetFramebufferSize( window, &SCREEN_WIDTH, &SCREEN_HEIGHT );
    
    // Set the required callback functions
    glfwSetKeyCallback( window, KeyCallback );
    glfwSetCursorPosCallback( window, MouseCallback );
    
    // GLFW Options
    //glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    // Initialize GLEW to setup the OpenGL Function pointers
    if ( GLEW_OK != glewInit( ) )
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );
    
    // OpenGL options
    glEnable( GL_DEPTH_TEST );
    
    // Setup and compile our shaders
    Shader shader( "Shader/modelLoading.vs", "Shader/modelLoading.frag" );
    
    // Load models
    Model pasto((char*)"Models/Campamento/pasto.obj");
    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
   
    Model tent((char*)"Models/Campamento/modern_camping_tent_(OBJ).obj");
    
    Model gato((char*)"Models/Campamento/gato.obj");
    
    Model perro((char*)"Models/Campamento/perro.obj");
   
    Model pollo((char*)"Models/Campamento/pollo.obj");
    
    Model venado((char*)"Models/Campamento/venado.obj");
    
    Model pino((char*)"Models/Campamento/pino.obj");
    
    Model tronco1((char*)"Models/Campamento/tronco.obj");
    
    Model tronco2((char*)"Models/Campamento/trunk_wood.obj");
    
    Model rocag((char*)"Models/Campamento/rocag.obj");
    
    Model rocap((char*)"Models/Campamento/rocap.obj");

    Model lampara((char*)"Models/Campamento/lampara.obj");

    Model fogata((char*)"Models/Campamento/fogata.obj");

    Model luna((char*)"Models/Campamento/luna.obj");

    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Set frame time
        GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Check and call events
        glfwPollEvents();
        DoMovement();

        // Clear the colorbuffer
        glClearColor(0.7f, 0.85f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();

        glm::mat4 view = camera.GetViewMatrix();
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        // Draw the loaded model
        //Pasto
        glm::mat4 model(1);
        model = glm::translate(model, glm::vec3(0.0f, -8.9f, 0.0f));
        model = glm::scale(model, glm::vec3(3.0f, 1.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pasto.Draw(shader);

        //Tienda
		model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-3.5f, -1.0f, -1.5f));
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tent.Draw(shader);

        //Gato
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-1.5f, 5.3f, -1.0f));
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
        model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        gato.Draw(shader);

        //Perro
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(2.0f, 0.9f, 0.5f));
        model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
        model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        perro.Draw(shader);

        //Pollo
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-0.5f, -1.3f, 8.0f));
        model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
        model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pollo.Draw(shader);

        //Venado
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 17.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        //model = glm::rotate(model, glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        venado.Draw(shader);

        //Pino
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-25.0f, -10.0f, -6.0f));
        model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        pino.Draw(shader);

		//Tronco 1
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-5.0f, -2.0f, -6.0f));
        model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
        model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tronco1.Draw(shader);

        //Tronco 2
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -0.8f));
        model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
        model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        tronco2.Draw(shader);

		//Roca grande
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-40.0f, -15.0f, 4.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        rocag.Draw(shader);

        //Lampara
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(-12.0f, -1.0f, -4.0f));
        model = glm::scale(model, glm::vec3(0.035f, 0.035f, 0.035f));  // Reducida significativamente
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        lampara.Draw(shader);

        //Fogata
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(12.0f, -1.0f, 4.0f));
        model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));  // Reducida significativamente
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        fogata.Draw(shader);

        //Luna
        model = glm::mat4(1);
        model = glm::translate(model, glm::vec3(12.0f, 95.0f, 4.0f));
        model = glm::scale(model, glm::vec3(95.0f, 95.0f, 95.0f));  // Reducida significativamente
        glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
        luna.Draw(shader);
        
        // Swap the buffers
        glfwSwapBuffers( window );
    }
    
    glfwTerminate( );
    return 0;
}


// Moves/alters the camera positions based on user input
void DoMovement( )
{
    // Camera controls
    if ( keys[GLFW_KEY_W] || keys[GLFW_KEY_UP] )
    {
        camera.ProcessKeyboard( FORWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN] )
    {
        camera.ProcessKeyboard( BACKWARD, deltaTime );
    }
    
    if ( keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT] )
    {
        camera.ProcessKeyboard( LEFT, deltaTime );
    }
    
    if ( keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT] )
    {
        camera.ProcessKeyboard( RIGHT, deltaTime );
    }

   
}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback( GLFWwindow *window, int key, int scancode, int action, int mode )
{
    if ( GLFW_KEY_ESCAPE == key && GLFW_PRESS == action )
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    
    if ( key >= 0 && key < 1024 )
    {
        if ( action == GLFW_PRESS )
        {
            keys[key] = true;
        }
        else if ( action == GLFW_RELEASE )
        {
            keys[key] = false;
        }
    }
 
}

void MouseCallback( GLFWwindow *window, double xPos, double yPos )
{
    if ( firstMouse )
    {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    
    GLfloat xOffset = xPos - lastX;
    GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left
    
    lastX = xPos;
    lastY = yPos;
    
    camera.ProcessMouseMovement( xOffset, yOffset );
}

