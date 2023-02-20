#pragma once

#include <cstdlib>
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class virtualObject
{

public:
    static virtualObject* newVirtualObject(
        std::vector<GLfloat>& vertexData,
        std::vector<GLfloat>& colorData,
        glm::vec3 position = {0, 0, 0}
    );
    ~virtualObject(){};

    void setPositon(glm::vec3 position);
    void setColorData(GLfloat* colorData);

    const glm::vec3 getPosition() const { return m_position; };
    const std::vector<GLfloat> getVertexData() const { return m_vertexData; };
    const std::vector<GLfloat> getColorData() const { return m_colorData; };
    const GLuint getShaderID() const { return m_shaderID; };
    const GLuint getMatrixID() const { return m_matrixID; };
    const GLuint getVertexBuffer() const { return m_vertexBuffer; };
    const GLuint getColorBuffer() const { return m_colorBuffer; };

private:
    virtualObject(
        glm::vec3 position,
        std::vector<GLfloat> vertexData,
        std::vector<GLfloat> colorData,
        GLuint shaderID,
        GLuint matrixID,
        GLuint vertexBuffer,
        GLuint colorBuffer
    );

    glm::vec3 m_position;
    std::vector<GLfloat> m_vertexData;
    std::vector<GLfloat> m_colorData;
    const GLuint m_shaderID;
    const GLuint m_matrixID;
    const GLuint m_vertexBuffer;
    const GLuint m_colorBuffer;

};