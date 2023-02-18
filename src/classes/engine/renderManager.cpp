
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderManager.h"
#include "../shader/loadShader.h"

renderManager* renderManager::m_instance = nullptr;
std::vector<virtualObject*> renderManager::m_sceneObjects;

renderManager* renderManager::getRenderManager()
{
    if ( m_instance == nullptr )
    {
        m_instance = new renderManager();
    }

    return m_instance;
}

renderManager::renderManager()
{
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };

    // One color for each vertex. They were generated randomly.
    static GLfloat g_color_buffer_data[12*3*3];
    for (int v = 0; v < 12*3 ; v++){
        g_color_buffer_data[3*v+0] = 0;
        g_color_buffer_data[3*v+1] = 0;
        g_color_buffer_data[3*v+2] = 0;
    }

    // Identify the vertex buffer
    GLuint vertexBuffer;
    // Generate a buffer with our identifier
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // Give vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "resources/shader/simpleVertexShader.vert", "resources/shader/simpleFragmentShader.frag" );
    // Get a handle for our "MVP" uniform
    // Only during the initialisation
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(
            glm::radians(45.0f),
            (float)1024 / (float)640,
            0.1f,
            100.0f
    );

    // Or, for an orthographic camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix : an identity matrix (model will be at the origin)
    glm::mat4 Model = glm::mat4(1.0f);
    // Our ModelViewProjection : multiplication of our 3 matrices
    glm::mat4 mvp = Projection * View * Model; // Matrix multiplication is the other way around
}

void renderManager::earlyRenderUpdate()
{

}

void renderManager::renderUpdate()
{
    /*
    TODO: Extract fps counter
    double currentTime = glfwGetTime();
    totalFrames++;
    if ( currentTime - lastTime >= 1.0 )
    {
        std::cout << "FPS: " + std::to_string(1000.0 / double(totalFrames)) + "\n";
        totalFrames = 0;
        lastTime += 1.0;
    }
     */
    /*

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
}

void renderManager::lateRenderUpdate()
{

}

void renderManager::addObjectToScene(virtualObject* object)
{
    m_sceneObjects.push_back(object);
}

void renderManager::removeObjectFromScene(virtualObject *object)
{
    m_sceneObjects.erase(std::remove(m_sceneObjects.begin(), m_sceneObjects.end(), object), m_sceneObjects.end());
}

void renderManager::removeObjectFromScene(int objectId)
{
    m_sceneObjects.erase(m_sceneObjects.begin() + objectId);
}

void renderManager::clearScene()
{
    for (virtualObject* object : m_sceneObjects)
    {
        delete(object);
    }
    m_sceneObjects.clear();
}