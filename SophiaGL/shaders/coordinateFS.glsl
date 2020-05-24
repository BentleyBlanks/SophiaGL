#version 330 core
in vec3 normal;
in vec2 texCoord;
out vec4 fragColor;

uniform float time;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main()
{
    //fragColor = vec4(normal, 1.0f);
    //fragColor = vec4(texCoord, 0.0f, 1.0f);
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    //vec4 texColor = texture(texture0, texCoord);
    //fragColor = texColor;

    //if(texCoord.x > 0.5f)
    //    texColor = texture(texture0, texCoord);
    //else
    //    texColor = texture(texture1, texCoord);

    //fragColor = time * color * texColor;
    //fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}