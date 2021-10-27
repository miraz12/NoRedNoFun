#pragma once
#include "ShaderProgram.hpp"

class QuadShaderProgram : public ShaderProgram {
public:
	QuadShaderProgram();
	~QuadShaderProgram() = default;

	void setupVertexAttributePointers() override;
};
