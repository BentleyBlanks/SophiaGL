#pragma once
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <core/util/s3UtilsIO.h>
#include <app/s3CallbackManager.h>
#include <app/s3Window.h>
#include <shader.h>

#include <imgui.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class s3App : public s3CallbackHandle
{
public:
	s3App()
	{
		std::vector<std::string> paths;
		paths.push_back("../../SophiaGL/thirdparty/fakeUnityShader/fake_unity_shader/shader_parser");
		paths.push_back("../../SophiaGL/thirdparty/fakeUnityShader/fake_unity_shader/shaders");

		shaderDirWatch = new s3UtilsDirectoryWatch();
		shaderDirWatch->watch("../../SophiaGL/thirdparty/fake_unity_shader/fake_unity_shader/shader_parser", false);
		//shaderDirWatch->watch(paths, false);

		info.api = ShaderGraphicsAPI::OpenGL;
		info.root_path = "../../SophiaGL/thirdparty/fake_unity_shader/fake_unity_shader/";
	}

	~s3App()
	{
		S3_SAFE_DELETE(shaderDirWatch);
	}

	void onHandle(const s3CallbackUserData* userData)
	{
		if (userData->sender == &s3CallbackManager::onEngineInit)
		{
			shader_init(info);

			const char* content = shader_load("shaders/openglTest.shader");
			printf("-----------------------------------------------------------------------\n");
		}
		else if (userData->sender == &s3CallbackManager::onUpdate)
		{
			if (shaderDirWatch->hasChanged())
			{
				// hotreload
				shader_init(info);
				const char* content = shader_load("shaders/openglTest.shader");
				printf("-----------------------------------------------------------------------\n");
			}
		}
		else if (userData->sender == &s3CallbackManager::onBeginRender)
		{
			ImGui::Begin("Sophia");
			if (ImGui::Button("Print Lua Stack"))
				shader_print_stack();

			ImGui::End();
		}
		else if (userData->sender == &s3CallbackManager::onEngineDeinit)
		{
			shader_cleanup();
		}
		else if (userData->sender == &s3CallbackManager::onWindowFocused)
		{
			//int* focused = (int*)userData->data;
			//if (shaderDirWatch->hasChanged() && *focused == 1)
			//{
			//	// hotreload
			//	shader_init(info);
			//	const char* content = shader_load("shaders/openglTest.shader");
			//}
		}
	}

	s3UtilsDirectoryWatch* shaderDirWatch = nullptr;
	ShaderInitInfo info;
};

int main()
{
	s3App app;
	s3CallbackManager::onEngineInit    += app;
	s3CallbackManager::onEngineDeinit  += app;
	s3CallbackManager::onUpdate        += app;
	s3CallbackManager::onWindowFocused += app;
	s3CallbackManager::onBeginRender   += app;

	s3Window& window = s3Window::getInstance();
	window.init("SophiaGL", 100, 100, 350, 200);
	window.run();
	
	return 0;
}