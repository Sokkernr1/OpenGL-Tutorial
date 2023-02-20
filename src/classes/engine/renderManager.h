#pragma once

#include <cstdlib>
#include <stdio.h>
#include <vector>

#include "virtualObject.h"

class renderManager {

public:
    static renderManager* getRenderManager();

    ~renderManager();

    void earlyRenderUpdate();
    void renderUpdate();
    void lateRenderUpdate();

    static void addObjectToScene(virtualObject* object);
    static void removeObjectFromScene(virtualObject* object);
    static void removeObjectFromScene(int objectId);
    static void clearScene();

    static void setCameraMatrix(glm::mat4 matrix) { m_cameraMatrix = matrix; };
    static void setProjectionMatrix(glm::mat4 matrix) { m_projectionMatrix = matrix; };

    static glm::mat4 getCameraMatrix() { return m_cameraMatrix; };
    static glm::mat4 getProjectionMatrix() { return m_projectionMatrix; };

private:
    renderManager();

    static renderManager* m_instance;

    static std::vector<virtualObject*> m_sceneObjects;
    static glm::mat4 m_cameraMatrix;
    static glm::mat4 m_projectionMatrix;

};