#include "windowManager.h"

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderManager.h"
#include "../shader/loadShader.h"

windowManager* windowManager::m_instance = nullptr;

windowManager::windowManager(char* windowTitle, int windowWidth, int windowHeight, int textureSamples)
    : m_gameWindow(nullptr)
    , m_textureSamples(textureSamples)
    , m_windowWidth(windowWidth)
    , m_windowHeight(windowHeight)
    , m_windowTitle(windowTitle)
{
}

windowManager* windowManager::getGameWindow(char* windowTitle, int windowWidth, int windowHeight, int textureSamples)
{
    if ( m_instance == nullptr )
    {
        m_instance = new windowManager(windowTitle, windowWidth, windowHeight, textureSamples);
    }
    return m_instance;
}

int windowManager::startWindow()
{
    // Initialise GLFW
    glewExperimental = true; //Needed for core profile
    if ( !glfwInit() )
    {
        fprintf(stderr, "Failed to initialize GLFW!\n");
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 3x Anti-Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Use version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow(1024, 640, "OpenGL", nullptr, nullptr);
    if ( window == nullptr )
    {
        fprintf(stderr, "Failed to open GLFW window...\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // Initiate GLEW
    glewExperimental = true; // Needed in the core profile
    if (glewInit() != GLEW_OK)
    {
        fprintf( stderr, "Failed to initialize GLEW...\n" );
        return -1;
    }

    glfwSetInputMode( window, GLFW_STICKY_KEYS, GL_TRUE);

    renderManager* RenderManager = renderManager::getRenderManager();

    do
    {
        RenderManager->renderUpdate();
        /*
        double currentTime = glfwGetTime();
        totalFrames++;
        if ( currentTime - lastTime >= 1.0 )
        {
            std::cout << "FPS: " + std::to_string(1000.0 / double(totalFrames)) + "\n";
            totalFrames = 0;
            lastTime += 1.0;
        }

        if ( g_color_buffer_data[3*0+2] >= 1 && colorChangeValue > 0.0f )
        {
            colorChangeValue = -0.01f;
        }
        else if ( g_color_buffer_data[3*0+2] <= 0 && colorChangeValue < 0.0f )
        {
            colorChangeValue = 0.01f;
        }

        for (int v = 0; v < 12*3 ; v++)
        {
            g_color_buffer_data[3 * v + 0] = g_color_buffer_data[3 * v + 0] + colorChangeValue;
            g_color_buffer_data[3 * v + 1] = g_color_buffer_data[3 * v + 1] + colorChangeValue;
            g_color_buffer_data[3 * v + 2] = g_color_buffer_data[3 * v + 2] + colorChangeValue;
        }

        glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

        // Use our shader
        glUseProgram(programID);

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glVertexAttribPointer(
                0,             // No particular reason for 0, but must match the layout in the shader
                3,             // Size
                GL_FLOAT,      // Type
                GL_FALSE,      // Normalized?
                0,             // Stride
                (void*)nullptr // Array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glVertexAttribPointer(
                1,             // No particular reason for 0, but must match the layout in the shader
                3,             // Size
                GL_FLOAT,      // Type
                GL_FALSE,      // Normalized?
                0,             // Stride
                (void*)nGLFWwindowullptr // Array buffer offset
        );

        // Drawing the object
        glDrawArrays(GL_TRIANGLES, 0, sizeof(g_vertex_buffer_data) / 3); // Start at vertex 0 -> 3 Vertices -> 1 Triangle
        glDisableVertexAttribArray(0);
         */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );

    return 0;
}

void windowManager::closeWindow()
{
    glfwSetWindowShouldClose(m_gameWindow, GLFW_TRUE);
}

void windowManager::setWindowTitle(std::string title)
{
    m_windowTitle = title.c_str();

    glfwSetWindowTitle(m_gameWindow, m_windowTitle);
}

void windowManager::setWindowDimensions(int width, int height)
{
    m_windowWidth = width;
    m_windowHeight = height;

    glfwSetWindowSize(m_gameWindow, m_windowWidth, m_windowHeight);
}
