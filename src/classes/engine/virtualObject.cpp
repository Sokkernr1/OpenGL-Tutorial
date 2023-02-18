#include "virtualObject.h"

virtualObject::virtualObject(glm::vec3 position, GLfloat *vertexData, GLfloat *colorData)
    : m_position(position)
    , m_vertexData(vertexData)
    , m_colorData(colorData)
{
}

virtualObject *virtualObject::newVirtualObject(
    GLfloat *vertexData,
    GLfloat *colorData,
    glm::vec3 position
)
{
    return new virtualObject(position, vertexData, colorData);
}

virtualObject *
virtualObject::newVirtualObject(
    std::vector<GLfloat> vertexData,
    std::vector<GLfloat> colorData,
    glm::vec3 position
)
{
    return new virtualObject(position, &vertexData[0], &colorData[0]);
}

void virtualObject::setPositon(glm::vec3 position)
{
    m_position = position;
}