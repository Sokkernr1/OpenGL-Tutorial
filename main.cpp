// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW. Always include it before gl.h and glfw3.h, since it's a bit magic.
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

int main()
{
    // Initialise GLFW
    glewExperimental = true; //Needed for core profile
    if ( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW!\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 3x Anti-Aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Use version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 640, "OpenGL", nullptr, nullptr );
    if ( window == nullptr )
    {
        fprintf( stderr, "Failed to open GLFW window...\n" );
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

    do
    {
        glClear( GL_COLOR_BUFFER_BIT ); //Clear the screen
        glfwSwapBuffers( window );
        glfwPollEvents();
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(window) == 0 );
}