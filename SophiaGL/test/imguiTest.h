#pragma once
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <app/s3CallbackManager.h>
#include <app/s3Window.h>

#include <glad/glad.h>
#include <imgui.h>

class s3App : public s3CallbackHandle
{
public:
    void onHandle(const s3CallbackUserData* userData)
    {
        if (userData->sender == &s3CallbackManager::onBeginRender)
        {
            static bool openWindow = true;
            ImGui::ShowDemoWindow(&openWindow);
        }
    }
};

int main()
{
    s3App app;
    s3CallbackManager::onEngineInit    += app;
    s3CallbackManager::onUpdate        += app;
    s3CallbackManager::onBeginRender   += app;
    s3CallbackManager::onWindowFocused += app;

    s3Window& window = s3Window::getInstance();
    window.init("SophiaGL", 100, 100, 1280, 720);
    window.run();

    return 0;
}