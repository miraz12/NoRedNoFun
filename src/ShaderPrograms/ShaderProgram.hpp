#pragma once
#include <string>

// Base shader class, inherit from this and define your own setupVertexAttributePointers that matches the shaders
class ShaderProgram {
public:
    ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath);
    virtual ~ShaderProgram();

    void loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath);
    void use();

    virtual void setupVertexAttributePointers() = 0;
    virtual unsigned int getUniformLocation(std::string uniformName) = 0;

protected:
    unsigned int p_shaderProgram;

private:

    void readFile(std::string filePath, std::string* result);
};
