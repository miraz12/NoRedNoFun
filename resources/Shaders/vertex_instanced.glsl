#version 440

// If inputs change, also update SimpleShaderProgram::setupVertexAttributePointers to match
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexCoords;
// Instanced attributes starts here
layout (location = 2) in mat4 modelMatrix;
layout (location = 6) in mat4 textureMatrix;
layout (location = 10) in int inTextureId;

// If uniforms change, also update SimpleShaderProgram to match
layout(location = 0) uniform mat4 viewMatrix = mat4(1.0); // Initialize as entity matrix for if no matrix is bound

// out vec4 color;
out vec2 texCoords;
out flat int textureId;

void main() {
    textureId = inTextureId;
    gl_Position = viewMatrix * modelMatrix * vec4(inPosition, 1.0);
//     color = inColor;
    texCoords = vec2(textureMatrix * vec4(inTexCoords, 0.0, 1.0));
}
