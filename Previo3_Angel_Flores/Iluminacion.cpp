//Ángel Joel Flores Torres
//Practica 8
//17/10/2025
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
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));
bool keys[1024];
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// Light attributes
// timeOfDay: Controla la hora del día usando radianes
float timeOfDay = 0.0f;  // 0 radianes = mediodía, PI radianes = medianoche // - 2*PI radianes = vuelve al mediodía (ciclo completo)
float cycleSpeed = 0.3f;  // Velocidad del ciclo // Multiplica el deltaTime para controlar la velocidad del ciclo
bool autoRotate = false;  // Rotación automática del ciclo. Si es true, timeOfDay se incrementa automáticamente cada frame
float lightRadius = 30.0f;  // Radio de la órbita de las luces. Determina qué tan lejos del centro se mueven las luces
float lightHeight = 20.0f;  // Altura base de las luces. Las luces rotan alrededor de este punto de altura

int main()
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 8 Angel Flores", nullptr, nullptr);

    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

    glfwSetKeyCallback(window, KeyCallback);
    glfwSetCursorPosCallback(window, MouseCallback);

    glewExperimental = GL_TRUE;
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    // Setup shaders
    Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
    Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");

    // Load models
    Model pasto((char*)"Models/Campamento/pasto.obj");
    Model tent((char*)"Models/Campamento/modern_camping_tent_(OBJ).obj");
    Model gato((char*)"Models/Campamento/gato.obj");
    Model perro((char*)"Models/Campamento/perro.obj");
    Model pollo((char*)"Models/Campamento/pollo.obj");
    Model venado((char*)"Models/Campamento/venado.obj");
    Model pino((char*)"Models/Campamento/pino.obj");
    Model tronco1((char*)"Models/Campamento/tronco.obj");
    Model tronco2((char*)"Models/Campamento/trunk_wood.obj");
    Model rocag((char*)"Models/Campamento/rocag.obj");

    glm::mat4 projection = glm::perspective(camera.GetZoom(), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // First, set the container's VAO (and VBO)
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

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

        // Actualizar ciclo día/noche si está activado
        if (autoRotate)
        {
            timeOfDay += cycleSpeed * deltaTime;
            if (timeOfDay > 2.0f * glm::pi<float>())
                timeOfDay -= 2.0f * glm::pi<float>();
        }

        // Calcular posiciones de las luces en órbita
        glm::vec3 sunPos(
            lightRadius * cos(timeOfDay),
            lightHeight + lightRadius * sin(timeOfDay),
            0.0f
        );

        glm::vec3 moonPos(
            lightRadius * cos(timeOfDay + glm::pi<float>()),
            lightHeight + lightRadius * sin(timeOfDay + glm::pi<float>()),
            0.0f
        );

        // Calcular intensidades según posición (cuando está sobre el horizonte)
        float sunIntensity = glm::max(0.0f, sin(timeOfDay));
        float moonIntensity = glm::max(0.0f, sin(timeOfDay + glm::pi<float>()));

        // Colores de fondo dinámicos
        float bgR = 0.1f + 0.6f * sunIntensity;
        float bgG = 0.2f + 0.65f * sunIntensity;
        float bgB = 0.3f + 0.7f * sunIntensity;
        glClearColor(bgR, bgG, bgB, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = camera.GetViewMatrix();

        // Función para renderizar todos los modelos
        auto renderModels = [&](Shader& shader) {
            glm::mat4 model(1);

            // Pasto
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(0.0f, -8.9f, 0.0f));
            model = glm::scale(model, glm::vec3(3.0f, 1.0f, 3.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            pasto.Draw(shader);

            // Tienda
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-3.5f, -1.0f, -1.5f));
            model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            tent.Draw(shader);

            // Gato
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-1.5f, 5.3f, -1.0f));
            model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
            model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            gato.Draw(shader);

            // Perro
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(2.0f, 0.9f, 0.5f));
            model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
            model = glm::rotate(model, glm::radians(-30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            perro.Draw(shader);

            // Pollo
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-0.5f, -1.3f, 8.0f));
            model = glm::scale(model, glm::vec3(1.9f, 1.9f, 1.9f));
            model = glm::rotate(model, glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            pollo.Draw(shader);

            // Venado
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-10.0f, -1.0f, 17.0f));
            model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            venado.Draw(shader);

            // Pino
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-25.0f, -10.0f, -6.0f));
            model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            pino.Draw(shader);

            // Tronco 1
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-5.0f, -2.0f, -6.0f));
            model = glm::scale(model, glm::vec3(1.2f, 1.2f, 1.2f));
            model = glm::rotate(model, glm::radians(15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            tronco1.Draw(shader);

            // Tronco 2
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-10.0f, -1.0f, -0.8f));
            model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
            model = glm::rotate(model, glm::radians(-25.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            tronco2.Draw(shader);

            // Roca grande
            model = glm::mat4(1);
            model = glm::translate(model, glm::vec3(-40.0f, -15.0f, 4.0f));
            model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
            glUniformMatrix4fv(glGetUniformLocation(shader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            rocag.Draw(shader);
            };

        // LUZ DEL SOL (DÍA)
        if (sunIntensity > 0.01f)
        {
            lightingShader.Use();
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"),
                sunPos.x, sunPos.y, sunPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
                camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

            // Propiedades luz del sol
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"),
                0.3f * sunIntensity, 0.3f * sunIntensity, 0.25f * sunIntensity);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"),
                1.0f * sunIntensity, 0.95f * sunIntensity, 0.8f * sunIntensity);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"),
                0.8f * sunIntensity, 0.8f * sunIntensity, 0.7f * sunIntensity);

            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

            // Material
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.6f, 0.6f, 0.6f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

            renderModels(lightingShader);
        }

        // LUZ DE LA LUNA (NOCHE) 
        if (moonIntensity > 0.01f)
        {
            // Habilitar blending para sumar iluminación
            if (sunIntensity > 0.01f)
            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);
                glDepthFunc(GL_EQUAL);
            }

            lightingShader.Use();
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.position"),
                moonPos.x, moonPos.y, moonPos.z);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "viewPos"),
                camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

            // Propiedades luz de la luna
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.ambient"),
                0.1f * moonIntensity, 0.12f * moonIntensity, 0.2f * moonIntensity);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.diffuse"),
                0.3f * moonIntensity, 0.35f * moonIntensity, 0.5f * moonIntensity);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "light.specular"),
                0.2f * moonIntensity, 0.25f * moonIntensity, 0.4f * moonIntensity);

            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(lightingShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

            // Material
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.ambient"), 0.6f, 0.6f, 0.6f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0.8f, 0.8f, 0.8f);
            glUniform3f(glGetUniformLocation(lightingShader.Program, "material.specular"), 0.5f, 0.5f, 0.5f);
            glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);

            renderModels(lightingShader);

            if (sunIntensity > 0.01f)
            {
                glDisable(GL_BLEND);
                glDepthFunc(GL_LESS);
            }
        }

        // RENDERIZAR LAS LÁMPARAS (SOL Y LUNA)
        lampShader.Use();
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));

        glBindVertexArray(VAO);

        // Sol 
        if (sunIntensity > 0.01f)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, sunPos);
            model = glm::scale(model, glm::vec3(2.0f));
            glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        // Luna 
        if (moonIntensity > 0.01f)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, moonPos);
            model = glm::scale(model, glm::vec3(1.5f));
            glUniformMatrix4fv(glGetUniformLocation(lampShader.Program, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
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

    // Control del ciclo día/noche
    if (keys[GLFW_KEY_SPACE] && action == GLFW_PRESS)
    {
        autoRotate = !autoRotate;  // Activar/desactivar rotación automática
    }

    // Control manual del tiempo
    if (keys[GLFW_KEY_O])
    {
        timeOfDay += 0.05f;  // Avanzar tiempo (hacia noche)
    }

    if (keys[GLFW_KEY_L])
    {
        timeOfDay -= 0.05f;  // Retroceder tiempo (hacia día)
    }

    // Ajustar velocidad del ciclo
    if (keys[GLFW_KEY_I])
    {
        cycleSpeed += 0.1f;
    }

    if (keys[GLFW_KEY_K])
    {
        cycleSpeed = glm::max(0.1f, cycleSpeed - 0.1f);
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