#pragma once

#include <core/s3Callback.h>

class s3CallbackManager
{
public:
    // only called once when engine is inited / deinit
    static s3Callback onEngineInit;
    static s3Callback onEngineDeinit;

    // called every frame in render loop
    static s3Callback onBeginRender;
    static s3Callback onEndRender;
    static s3Callback onUpdate;
     
    // called when mouseEvent triggered
    static s3Callback onMousePressed;
    static s3Callback onMouseMoved;
    static s3Callback onMouseReleased;
    static s3Callback onMouseScrolled;

    // called when keyEvent triggered
    static s3Callback onKeyPressed;
    static s3Callback onKeyReleased;
};

// add / remove the system callbacks
void s3CallbackInit();
void s3CallbackDeinit();
