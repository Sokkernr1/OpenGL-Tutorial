#pragma once

#include <cstdlib>
#include <stdio.h>
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>

class virtualObject
{

public:
    virtualObject* newVirtualObject(
        GLfloat* vertexData,
        GLfloat* colorData = nullptr,
        glm::vec3 position = {0, 0, 0}
    );
    virtualObject* newVirtualObject(
        std::vector<GLfloat> vertexData,
        std::vector<GLfloat> colorData = {},
        glm::vec3 position = {0, 0, 0}
    );
    ~virtualObject(){};

    void setPositon(glm::vec3 position);
    void setColorData(GLfloat* colorData);

    const glm::vec3 getPosition() const { return m_position; };
    const GLfloat* getVertexData() const { return m_vertexData; };
    const GLfloat* getColorData() const { return m_colorData; };

private:
    virtualObject(
        glm::vec3 position,
        GLfloat* vertexData,
        GLfloat* colorData
    );

    glm::vec3 m_position;
    const GLfloat* m_vertexData;
    GLfloat* m_colorData;

};