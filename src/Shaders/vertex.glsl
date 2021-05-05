#version 460 core

// If inputs change, also update SimpleShaderProgram::setupVertexAttributePointers to match
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoords;

// If uniforms change, also update SimpleShaderProgram to match
layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewMatrix;

out vec3 color;
out vec2 texCoords;

void main() {
    gl_Position = viewMatrix * modelMatrix * vec4(inPosition, 1.0);
    color = inColor;
    texCoords = inTexCoords;
}
