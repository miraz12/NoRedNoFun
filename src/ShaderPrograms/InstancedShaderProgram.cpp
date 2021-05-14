#include "InstancedShaderProgram.hpp"

#include <iostream>

#include <glad/glad.h>

InstancedShaderProgram::InstancedShaderProgram() :
	ShaderProgram("../../src/Shaders/vertex_instanced.glsl", "../../src/Shaders/fragment_instanced.glsl") {

	// Change if uniforms change in shaders, the map's values are set to match layout(location = x) in shaders.
	m_uniformBindings["viewMatrix"] = 0;
	m_uniformBindings["texture0"] = 1;
	m_uniformBindings["useTexture"] = 2;

	use(); // Start using the shader

	// Set texture0 uniform to be texture unit 0
	glUniform1i(m_uniformBindings["texture0"], 0);
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

	// Model Matrix
	for (unsigned int i = 0; i < 4; i++) {
		glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, totalFloats * sizeof(float), (void*) (4 * i * sizeof(float)));
		glEnableVertexAttribArray(2 + i);
		glVertexAttribDivisor(2 + i, 1);
	}

	// Texture Matrix
	for (unsigned int i = 0; i < 4; i++) {
		glVertexAttribPointer(6 + i, 4, GL_FLOAT, GL_FALSE, totalFloats * sizeof(float), (void*) ((16 + 4 * i) * sizeof(float)));
		glEnableVertexAttribArray(6 + i);
		glVertexAttribDivisor(6 + i, 1);
	}
}

unsigned int InstancedShaderProgram::getUniformLocation(std::string uniformName) {
	if (m_uniformBindings.find(uniformName) == m_uniformBindings.end()) {
		std::cout << "No uniform with name " << uniformName << "\n";
	}
	else {
		return m_uniformBindings[uniformName];
	}

	return NULL;
}
