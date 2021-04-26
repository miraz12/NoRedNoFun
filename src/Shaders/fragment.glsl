#version 460 core
precision highp float;

in vec3 color;
in vec2 texCoords;

uniform sampler2D sTexture;
uniform int useTexture;

out vec4 FragColor;

void main()
{
    if (useTexture == 1) {
        FragColor = texture(sTexture, texCoords);
    }
    else {
       FragColor = vec4(color, 1.0f);
    }

}
