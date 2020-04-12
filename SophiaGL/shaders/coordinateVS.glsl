#version 330 core
layout(location = 0) in vec3 positionWS;
//layout(location = 1) in vec3 vColor;
layout(location = 1) in vec2 vTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//out vec4 color;
out vec2 texCoord;

void main()
{
	gl_Position = projection * view * model * vec4(positionWS, 1.0f);
	//color       = vec4(vColor, 1.0f);
	texCoord    = vTexCoord;
}