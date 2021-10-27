#pragma once

#include "../ShaderProgram.hpp"

class CrtEffect : public ShaderProgram {
public:
    CrtEffect();
    ~CrtEffect() = default;
	void setupVertexAttributePointers() override;
};