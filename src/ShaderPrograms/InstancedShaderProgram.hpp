#pragma once
#include "ShaderProgram.hpp"

#include <utility>
#include <unordered_map>

class InstancedShaderProgram : public ShaderProgram {
public:
	InstancedShaderProgram();
	~InstancedShaderProgram();

	void setupVertexAttributePointers();
	void setupInstancedVertexAttributePointers();
	unsigned int getUniformLocation(std::string uniformName);
private:
	std::unordered_map<std::string, unsigned int> m_uniformBindings;
};
