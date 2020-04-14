#pragma once

#include <core/s3Settings.h>
#include <core/s3Timer.h>
#include <glm/glm.hpp>

class s3Window;
class s3App
{
public:
    s3App();
    ~s3App();

    bool init(const glm::vec2& size, const glm::vec2& pos);
    void run();
    void setClearColor(glm::vec4 clearColor);

    s3Window* getWindow();

	// get elapsed time when app is running
	float getTimeElapsed();

private:
    void shutdown();
    void render();

    s3Window* window;
    glm::vec4 clearColor;
	s3Timer timer;
};