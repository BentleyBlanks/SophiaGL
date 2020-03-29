#version 330 core
layout(location = 0) in vec3 positionWS;
layout(location = 1) in vec3 color;

out vec4 vertexColor;

void main()
{
   gl_Position = vec4(positionWS.xyz, 1.0);
   vertexColor = vec4(color, 1.0);
}