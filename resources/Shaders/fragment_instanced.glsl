#version 440

#define numTextures 15 

precision highp float;

// in vec4 color;
in vec2 texCoords;
in flat int textureId;

// If uniforms change, also update InstancedShaderProgram to match
layout(location = 1) uniform sampler2D textures[numTextures];

out vec4 FragColor;

mat4 thresholdMatrix = mat4(
    1.0, 9.0, 3.0, 11.0,
    13.0, 5.0, 15.0, 7.0,
    4.0, 12.0, 2.0, 10.0,
    16.0, 8.0, 14.0, 6.0
    );

void main()
{
    FragColor = vec4(0.0, 1.0, 0.0, 1.0);
    
    if (textureId < numTextures) {
        FragColor = texture(textures[textureId], texCoords);
    }


    // Screen-door transparancy
    float threshold = thresholdMatrix[int(floor(mod(gl_FragCoord.x, 4)))][int(floor(mod(gl_FragCoord.y, 4)))] / 17;
    if (threshold >= FragColor.a) {
        discard;
    }
}
