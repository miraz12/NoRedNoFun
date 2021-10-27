#pragma once
#include "ShaderProgram.hpp"

class InstancedShaderProgram : public ShaderProgram {
public:
	InstancedShaderProgram();
	~InstancedShaderProgram();

	void setupVertexAttributePointers() override;
	void setupInstancedVertexAttributePointers();
};
