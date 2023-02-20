
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderManager.h"
#include "virtualObject.h"
#include "../shader/loadShader.h"

renderManager* renderManager::m_instance = nullptr;
std::vector<virtualObject*> renderManager::m_sceneObjects;
glm::mat4 renderManager::m_cameraMatrix;
glm::mat4 renderManager::m_projectionMatrix;

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
    static std::vector<GLfloat> g_vertex_buffer_data {
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
    static std::vector<GLfloat>  g_color_buffer_data(12*3*3);
    for (int v = 0; v < 12*3 ; v++){
        g_color_buffer_data[3*v+0] = .9f;
        g_color_buffer_data[3*v+1] = .9f;
        g_color_buffer_data[3*v+2] = .9f;
    }
    virtualObject* newObject1 = virtualObject::newVirtualObject(g_vertex_buffer_data, g_color_buffer_data, glm::vec3(10.f, 10.f, 10.f));
    //virtualObject* newObject2 = virtualObject::newVirtualObject(g_vertex_buffer_data, g_color_buffer_data, glm::vec3(-1.f, -1.f, -1.f));

    addObjectToScene(newObject1);
    //addObjectToScene(newObject2);

    //TODO: Create a player camera class

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    m_projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (float)1024 / (float)640,
            0.1f,
            100.0f
    );

    // Or, for an orthographic camera :
    //glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates

    // Camera matrix
    m_cameraMatrix = glm::lookAt(
            glm::vec3(4,3,-3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glClearColor(.0f, .0f, .2f, .0f);
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

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clear the screen

    for (virtualObject* object : m_sceneObjects)
    {
        glBufferData(GL_ARRAY_BUFFER, object->getColorData().size() * 4, &object->getColorData()[0], GL_STATIC_DRAW);

        // Use our shader
        glUseProgram(object->getShaderID());

        // MVP = Projection * View * Model (Matrix calculations are the other way around)
        glm::mat4 mvp = m_projectionMatrix * m_cameraMatrix * glm::mat4(1.0f);
        //mvp = glm::translate(mvp, glm::vec3(1.0f, 1.0f, 1.0f));

        // Send our transformation to the currently bound shader, in the "MVP" uniform
        // This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
        glUniformMatrix4fv(object->getMatrixID(), 1, GL_FALSE, &mvp[0][0]);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, object->getVertexBuffer());
        glVertexAttribPointer(
                0,             // No particular reason for 0, but must match the layout in the shader
                3,             // Size
                GL_FLOAT,      // Type
                GL_FALSE,      // Normalized?
                0,             // Stride
                (void*)nullptr // Array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, object->getColorBuffer());
        glVertexAttribPointer(
                1,             // No particular reason for 0, but must match the layout in the shader
                3,             // Size
                GL_FLOAT,      // Type
                GL_FALSE,      // Normalized?
                0,             // Stride
                (void*) nullptr // Array buffer offset
        );

        // Drawing the object
        glDrawArrays(GL_TRIANGLES, 0, object->getVertexData().size() / 3); // Start at vertex 0 -> 3 Vertices -> 1 Triangle
    }
    glDisableVertexAttribArray(0);

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