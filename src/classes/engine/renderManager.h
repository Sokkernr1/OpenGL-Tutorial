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

private:
    renderManager();

    static renderManager* m_instance;

    static std::vector<virtualObject*> m_sceneObjects;

};