#pragma once

#include <vector>

class renderManager {
public:
    renderManager(){};
    void prepareRender();
private:
    std::vector<std::pair<std::string, int>> awd;
};