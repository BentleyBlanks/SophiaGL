#pragma once

#include <core/s3Callback.h>

//class s3Callbacks
//{
//public:
//    s3Callback onEngineInit;
//    s3Callback onEngineDeinit;
//    s3Callback onBeginRender;
//    s3Callback onEndRender;
//    s3Callback onUpdate;
//
//    s3Callback onMousePressed;
//    s3Callback onMouseMoved;
//    s3Callback onMouseReleased;
//    s3Callback onMouseScrolled;
//    s3Callback onKeyPressed;
//    s3Callback onKeyReleased;
//};

class s3CallbackManager
{
public:
    //static s3Callbacks callBack;
    static s3Callback onEngineInit;
    static s3Callback onEngineDeinit;
    static s3Callback onBeginRender;
    static s3Callback onEndRender;
    static s3Callback onUpdate;
     
    static s3Callback onMousePressed;
    static s3Callback onMouseMoved;
    static s3Callback onMouseReleased;
    static s3Callback onMouseScrolled;

    static s3Callback onKeyPressed;
    static s3Callback onKeyReleased;
};

// add / remove the system callbacks
void s3CallbackInit();
void s3CallbackDeinit();
