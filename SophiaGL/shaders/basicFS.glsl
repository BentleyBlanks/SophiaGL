#version 330 core
in vec4 color;
in vec2 texCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    vec4 texColor;
    if(texCoord.x > 0.5f)
        texColor = texture(texture0, texCoord);
    else
        texColor = texture(texture1, texCoord);

    fragColor = time * color * texColor;
}