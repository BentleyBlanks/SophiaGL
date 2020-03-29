#version 330 core
in vec4 color;
in vec2 texCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D testTexture;

void main()
{
//    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    vec4 texColor = texture(testTexture, texCoord);
    fragColor = time * color * texColor;
}