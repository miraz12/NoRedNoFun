#include "InstancedShaderProgram.hpp"

#include <iostream>

#include <glad/glad.h>

InstancedShaderProgram::InstancedShaderProgram() :
	ShaderProgram("resources/Shaders/vertex_instanced.glsl", "resources/Shaders/fragment_instanced.glsl") {

	// Change if uniforms change in shaders, the map's values are set to match layout(location = x) in shaders.
	m_uniformBindings["viewMatrix"] = 0;
	m_uniformBindings["textures"] = 1;

	use(); // Start using the shader

	// Set textures uniform
	int texturesArray[15] = {0};
	for (unsigned int i = 0; i < 15; i++) {
		texturesArray[i] = i;
	}
	glUniform1iv(m_uniformBindings["textures"], 15, texturesArray);
}

InstancedShaderProgram::~InstancedShaderProgram() {

}

void InstancedShaderProgram::setupVertexAttributePointers() {
	// Change if input layout changes in shaders
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void InstancedShaderProgram::setupInstancedVertexAttributePointers() {
	unsigned int totalFloats = 4 * 4 * 2; // Mat4 * 2
	unsigned int totalInts = 1;

	size_t stride = totalFloats * sizeof(float) + totalInts * sizeof(int);

	// Model Matrix
	for (unsigned int i = 0; i < 4; i++) {
		glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, stride, (void*) (4 * i * sizeof(float)));
		glEnableVertexAttribArray(2 + i);
		glVertexAttribDivisor(2 + i, 1);
	}

	// Texture Matrix
	for (unsigned int i = 0; i < 4; i++) {
		glVertexAttribPointer(6 + i, 4, GL_FLOAT, GL_FALSE, stride, (void*) ((16 + 4 * i) * sizeof(float)));
		glEnableVertexAttribArray(6 + i);
		glVertexAttribDivisor(6 + i, 1);
	}

	// Texture index
	glVertexAttribIPointer(10, 1, GL_INT, stride, (void*) (totalFloats * sizeof(float)));
	glEnableVertexAttribArray(10);
	glVertexAttribDivisor(10, 1);
}
