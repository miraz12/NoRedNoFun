#pragma once

#include "../Textures/SpriteMap.hpp"

#include <vector>

struct InstanceData;

class Quad: public SpriteMap {
public:
    Quad(std::vector<InstanceData>* matrices, unsigned int quadIndex);
    virtual ~Quad();

	glm::mat4& getModelMatrix();
    unsigned int getQuadIndex();
    void setTextureIndex(unsigned int index);

private:
    std::vector<InstanceData>* m_quadData;
    unsigned int m_quadIndex;
};
