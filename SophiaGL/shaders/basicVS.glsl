#version 330 core
layout(location = 0) in vec3 positionWS;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 vTexCoord;

out vec4 color;
out vec2 texCoord;

void main()
{
   gl_Position = vec4(positionWS.xyz, 1.0f);
   color       = vec4(vColor, 1.0f);
   texCoord    = vTexCoord;
}