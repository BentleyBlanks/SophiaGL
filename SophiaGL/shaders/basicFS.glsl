#version 330 core
in vec4 vertexColor;
uniform float time;
out vec4 fragColor;

void main()
{
//    fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    fragColor = time * vertexColor;
}