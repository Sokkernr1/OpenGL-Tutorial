#include "virtualObject.h"
#include "../shader/loadShader.h"

virtualObject::virtualObject(
    glm::vec3 position,
    std::vector<GLfloat> vertexData,
    std::vector<GLfloat> colorData,
    GLuint shaderID,
    GLuint matrixID,
    GLuint vertexBuffer,
    GLuint colorBuffer
)
    : m_position(position)
    , m_vertexData(vertexData)
    , m_colorData(colorData)
    , m_shaderID(shaderID)
    , m_matrixID(matrixID)
    , m_vertexBuffer(vertexBuffer)
    , m_colorBuffer(colorBuffer)
{
}

virtualObject* virtualObject::newVirtualObject(
    std::vector<GLfloat>& vertexData,
    std::vector<GLfloat>& colorData,
    glm::vec3 position
)
{
    GLuint shaderID = LoadShaders( "resources/shader/simpleVertexShader.vert", "resources/shader/simpleFragmentShader.frag" );
    GLuint MatrixID = glGetUniformLocation(shaderID, "MVP");

    // Identify the vertex buffer
    GLuint vertexBuffer;
    // Generate a buffer with our identifier
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    // Give vertices to OpenGL
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * 4, vertexData.data(), GL_STATIC_DRAW);

    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);

    glBufferData(GL_ARRAY_BUFFER, colorData.size() * 4, &colorData[0], GL_STATIC_DRAW);

    return new virtualObject(position, vertexData, colorData, shaderID, MatrixID, vertexBuffer, colorBuffer);
}

void virtualObject::setPositon(glm::vec3 position)
{
    m_position = position;
}