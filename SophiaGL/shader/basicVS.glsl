#version 330 core
layout (loction = 0) in vec3 PositionWS

void main()
{
    gl_Position = vec4(PositionWS.xyz, 1.0);
}