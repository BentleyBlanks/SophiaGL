#pragma once
#include <iostream>

#include <shader.h>
#include <shader_parser_gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


int main()
{
	shader_init();

	const char* content = shader_load("");
	printf("%s", content);

	shader_cleanup();
	
	return 0;
}