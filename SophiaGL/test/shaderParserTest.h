#pragma once
#include <iostream>

#define GRAPHICS_API_OPENGL
#include <shader.h>
#include <shader_parser_gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


int main()
{
	ShaderInitInfo info;
	info.api = ShaderGraphicsAPI::OpenGL;
	shader_init(info);

	const char* content = shader_load("");
	printf("%s", content);

	shader_cleanup();
	
	return 0;
}