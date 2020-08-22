#pragma once
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <core/util/s3UtilsIO.h>
#include <app/s3CallbackManager.h>
#include <app/s3Window.h>

#define GRAPHICS_API_OPENGL
#include <shader.h>
#include <shader_parser_gl.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class s3App : public s3CallbackHandle
{
public:
	s3App()
	{
		shaderDirWatch = new s3UtilsDirectoryWatch();
		shaderDirWatch->watch(path.c_str());

		info.api = ShaderGraphicsAPI::OpenGL;
		info.root_path = path.c_str();
	}

	~s3App()
	{
		S3_SAFE_DELETE(shaderDirWatch);
	}

	void onHandle(const s3CallbackUserData* userData)
	{
		bool dirHasChanged = shaderDirWatch->hasChanged();

		if (userData->sender == &s3CallbackManager::onEngineInit)
		{
			shader_init(info);

			const char* content = shader_load("shaders/openglTest.shader");
			printf("%s", content);
		}
		else if (userData->sender == &s3CallbackManager::onUpdate)
		{
			//if (dirHasChanged)
			{

			}
		}
		else if (userData->sender == &s3CallbackManager::onEngineDeinit)
		{
			shader_cleanup();
		}
		else if (userData->sender == &s3CallbackManager::onWindowFocused)
		{
			shader_init(info);
			const char* content = shader_load("shaders/openglTest.shader");
			printf("%s", content);
		}
	}

	std::string path = "../../SophiaGL/thirdparty/fakeUnityShader/fake_unity_shader/";
	s3UtilsDirectoryWatch* shaderDirWatch = nullptr;
	ShaderInitInfo info;
};

int main()
{
	s3App app;
	s3CallbackManager::onEngineInit    += app;
	s3CallbackManager::onUpdate        += app;
	s3CallbackManager::onWindowFocused += app;

	s3Window& window = s3Window::getInstance();
	window.init("SophiaGL", 100, 100, 1280, 720);
	window.run();
	
	return 0;
}