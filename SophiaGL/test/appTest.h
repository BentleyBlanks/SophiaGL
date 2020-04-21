#pragma once
#include <core/log/s3Log.h>
#include <app/s3App.h>

int main()
{
    s3App& app = s3App::getInstance();
    app.init("SophiaGL", 100, 100, 1280, 720);
    app.run();

    return 0;
}