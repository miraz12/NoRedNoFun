#include "ShaderProgram.hpp"

#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>

ShaderProgram::ShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
    loadShaders(vertexShaderPath, fragmentShaderPath);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(p_shaderProgram);
}

void ShaderProgram::loadShaders(std::string vertexShaderPath, std::string fragmentShaderPath) {
    // vertex shader
    std::string vertexShaderString = "";
    readFile(vertexShaderPath, &vertexShaderString);
    const char* vertexShaderSrc = vertexShaderString.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // fragment shader
    std::string fragmentShaderString = "";
    readFile(fragmentShaderPath, &fragmentShaderString);
    const char* fragmentShaderSrc = fragmentShaderString.c_str();

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // link shaders
    glDeleteProgram(p_shaderProgram); // Delete in case this is not the first time this shader is created.

    p_shaderProgram = glCreateProgram();
    glAttachShader(p_shaderProgram, vertexShader);
    glAttachShader(p_shaderProgram, fragmentShader);
    glLinkProgram(p_shaderProgram);

    // check for linking errors
    glGetProgramiv(p_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(p_shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void ShaderProgram::use() {
    glUseProgram(p_shaderProgram);
}

void ShaderProgram::setupInstancedVertexAttributePointers() {}

unsigned int ShaderProgram::getUniformLocation(std::string uniformName) {
	if (m_uniformBindings.find(uniformName) == m_uniformBindings.end()) {
		std::cout << "No uniform with name " << uniformName << "\n";
	}
	else {
		return m_uniformBindings[uniformName];
	}
    return 0;
}

void ShaderProgram::readFile(std::string filePath, std::string* result) {
    std::string line;
    std::ifstream theFile(filePath);
    if(theFile.is_open()) {
        while (std::getline(theFile, line)) {
            result->append(line + "\n");
        }
        theFile.close();
    }
    else {
        std::cout << "Could not open file " << filePath << "\n";
    }
}
