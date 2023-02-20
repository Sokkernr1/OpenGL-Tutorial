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
