#include <app/s3CallbackManager.h>
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <app/s3Window.h>

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

s3Callback s3CallbackManager::onWindowFocused;

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
        //else if (data->sender == &s3CallbackManager::onEngineInit)
        //{
        //    s3ImGuiInit((GLFWwindow*)data->data);
        //}
        //else if (data->sender == &s3CallbackManager::onEngineDeinit)
        //{
        //    s3ImGuiShutdown();
        //}
        //else if (data->sender == &s3CallbackManager::onBeginRender)
        //{
        //    s3ImGuiBeginRender();
        //}
        //else if (data->sender == &s3CallbackManager::onEndRender)
        //{
        //    s3ImGuiEndRender();
        //}
        //else if (data->sender == &s3CallbackManager::onKeyPressed)
        //{
        //    s3KeyEvent* keyEvent = (s3KeyEvent*)data->data;
        //    keyEvent->print();
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

    s3CallbackManager::onWindowFocused += systemHandler;
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

    s3CallbackManager::onWindowFocused -= systemHandler;
}
