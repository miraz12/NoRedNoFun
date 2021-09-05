#pragma once

#include "../Textures/SpriteMap.hpp"

#include <vector>

class Quad: public SpriteMap {
public:
    Quad(std::vector<glm::mat4>* matrices, unsigned int matrixIndex);
    virtual ~Quad();

	glm::mat4& getModelMatrix();
    unsigned int getMatrixIndex();

private:
    std::vector<glm::mat4>* m_matrices;
    unsigned int m_matrixIndex;
};
