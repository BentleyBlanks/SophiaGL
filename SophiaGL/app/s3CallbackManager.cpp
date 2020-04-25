#include <app/s3CallbackManager.h>
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <glfw/glfw3.h>
#include <app/s3Window.h>
//#include <core/s3Gui.h>
//#include <imgui.h>

s3Callback s3CallbackManager::onEngineInit;
s3Callback s3CallbackManager::onEngineDeinit;
s3Callback s3CallbackManager::onBeginRender;
s3Callback s3CallbackManager::onEndRender;
s3Callback s3CallbackManager::onUpdate;

s3Callback s3CallbackManager::onMousePressed;
s3Callback s3CallbackManager::onMouseMoved;
s3Callback s3CallbackManager::onMouseReleased;
s3Callback s3CallbackManager::onMouseScrolled;
s3Callback s3CallbackManager::onKeyPressed;
s3Callback s3CallbackManager::onKeyReleased;

// handle system's event
struct s3SystemHandler : public s3CallbackHandle
{
    void onHandle(const s3CallbackUserData* data)
    {
        if (data->sender == &s3CallbackManager::onKeyReleased)
        {
            s3KeyEvent* keyEvent = (s3KeyEvent*)data->data;
            keyEvent->print();

            if (keyEvent->keyType == s3KeyType::escape)
                s3Window::getInstance().shutdown();
        }
        //else if (data->sender == &s3CallbackManager::onKeyPressed)
        //{
        //    s3KeyEvent* keyEvent = (s3KeyEvent*)data->data;
        //    keyEvent->print();
        //}
        //else if (data->sender == &s3CallbackManager::callBack.onEngineInit)
        //{
        //    s3ImGuiInit(data->data, s3Renderer::get().getDevice(), s3Renderer::get().getDeviceContext());
        //}
        //else if (data->sender == &s3CallbackManager::callBack.onEngineDeinit)
        //{
        //    s3ImGuiShutdown();
        //}
        //else if (data->sender == &s3CallbackManager::callBack.onBeginRender)
        //{
        //    s3ImGuiBeginRender();
        //}
        //else if (data->sender == &s3CallbackManager::callBack.onEndRender)
        //{
        //    s3ImGuiEndRender();
        //}
    }
};

s3SystemHandler systemHandler;

void s3CallbackInit()
{
    s3CallbackManager::onBeginRender   += systemHandler;
    s3CallbackManager::onEndRender     += systemHandler;
    s3CallbackManager::onEngineDeinit  += systemHandler;
    s3CallbackManager::onEngineInit    += systemHandler;
    s3CallbackManager::onUpdate        += systemHandler;

    s3CallbackManager::onMousePressed  += systemHandler;
    s3CallbackManager::onMouseMoved    += systemHandler;
    s3CallbackManager::onMouseReleased += systemHandler;
    s3CallbackManager::onMouseScrolled += systemHandler;

    s3CallbackManager::onKeyPressed    += systemHandler;
    s3CallbackManager::onKeyReleased   += systemHandler;
}

void s3CallbackDeinit()
{
    s3CallbackManager::onBeginRender   -= systemHandler;
    s3CallbackManager::onEndRender     -= systemHandler;
    s3CallbackManager::onEngineDeinit  -= systemHandler;
    s3CallbackManager::onEngineInit    -= systemHandler;
    s3CallbackManager::onUpdate        -= systemHandler;

    s3CallbackManager::onMousePressed  -= systemHandler;
    s3CallbackManager::onMouseMoved    -= systemHandler;
    s3CallbackManager::onMouseReleased -= systemHandler;
    s3CallbackManager::onMouseScrolled -= systemHandler;

    s3CallbackManager::onKeyPressed    -= systemHandler;
    s3CallbackManager::onKeyReleased   -= systemHandler;
}
