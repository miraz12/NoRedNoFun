#version 440

// If inputs change, also update SimpleShaderProgram::setupVertexAttributePointers to match
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoords;

// If uniforms change, also update SimpleShaderProgram to match
layout(location = 0) uniform mat4 modelMatrix = mat4(1.0); // Initialize as entity matrix for if no matrix is bound
layout(location = 1) uniform mat4 viewMatrix = mat4(1.0); // Initialize as entity matrix for if no matrix is bound
layout(location = 2) uniform mat4 textureMatrix = mat4(1.0); // Initialize as entity matrix for if no matrix is bound

out vec4 color;
out vec2 texCoords;

void main() {
    gl_Position = viewMatrix * modelMatrix * vec4(inPosition, 1.0);
    color = inColor;
    texCoords = vec2(textureMatrix * vec4(inTexCoords, 0.0, 1.0));
}
