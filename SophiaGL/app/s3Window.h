#pragma once
#include <core/s3Settings.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class s3Window
{
public:
    s3Window(const char* caption, WNDPROC proc, const glm::vec2& size, const glm::vec2& pos);
    ~s3Window();

    glm::vec2 getCursorPosition();
    glm::vec2 getWindowSize();
    void resize(int width, int height);

    t3Vector2f getWindowPosition();
    void setWindowPosition(int x, int y);

    GLFWwindow* getHandle();

private:
    void adjustWindow();

    GLFWwindow* window;
    glm::vec2 size;
    glm::vec2 position;
};