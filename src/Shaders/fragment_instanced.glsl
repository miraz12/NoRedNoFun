#version 460 core
precision highp float;

// in vec4 color;
in vec2 texCoords;

// If uniforms change, also update SimpleShaderProgram to match
layout(location = 1) uniform sampler2D texture0;

out vec4 FragColor;

void main()
{
	FragColor = texture(texture0, texCoords);
}
