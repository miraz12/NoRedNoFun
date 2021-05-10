#pragma once

#include "../ShaderPrograms/ShaderProgram.hpp"

class InstancedQuadManager {
public:
	InstancedQuadManager(ShaderProgram &shaderProgram);
	~InstancedQuadManager();

private:
	ShaderProgram& m_shaderProgram;

	unsigned int m_instanceVBO;
};