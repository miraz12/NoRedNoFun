#version 440

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main() {
    vec3 col = texture(screenTexture, texCoords).rgb;
    FragColor = vec4(col, 1.0);
}