#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>

class windowManager
{
public:
    static windowManager* getGameWindow(
        char* windowTitle = nullptr,
        int windowWidth = 1200,
        int windowHeight = 600,
        int textureSamples = 4
    );

    int startWindow();
    void closeWindow();

    GLFWwindow* getWindow() const { return m_gameWindow; };
    int getTextureSamples() const { return m_textureSamples; };
    std::string getWindowTitle() const { return m_windowTitle; };
    std::vector<int> getWindowDimensions() const { return std::vector<int> {m_windowWidth, m_windowHeight}; };

    void setWindowTitle(std::string title);
    void setWindowDimensions(int width, int height);
private:
    windowManager(char* windowTitle, int windowWidth, int windowHeight, int textureSamples);

    static windowManager* m_instance;

    GLFWwindow* m_gameWindow;
    const int m_textureSamples;
    const char* m_windowTitle;
    int m_windowWidth;
    int m_windowHeight;

};
