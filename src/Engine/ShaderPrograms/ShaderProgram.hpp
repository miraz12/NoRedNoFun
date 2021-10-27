#pragma once
#include <string>
#include <unordered_map>

// Base shader class, inherit from this and define your own setupVertexAttributePointers that matches the shaders
class ShaderProgram {
public:
    ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
    virtual ~ShaderProgram();

    unsigned int getUniformLocation(std::string uniformName);
    void loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath);
    void use();

    virtual void setupVertexAttributePointers() = 0;
	virtual void setupInstancedVertexAttributePointers();

protected:
    unsigned int p_shaderProgram;
    std::unordered_map<std::string, unsigned int> m_uniformBindings;

private:

    void readFile(std::string filePath, std::string* result);
};
