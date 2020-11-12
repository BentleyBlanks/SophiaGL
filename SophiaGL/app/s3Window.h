#pragma once

#include <core/s3Settings.h>
#include <core/s3Timer.h>
#include <core/s3Event.h>
#include <glm/glm.hpp>

typedef struct GLFWwindow GLFWwindow;
class s3Window
{
public:
    static s3Window& getInstance() { return instance; }

    bool init(const char* title, int x, int y, int width, int height);
    void run();
    void shutdown();

    void setClearColor(float r, float g, float b, float a) { clearColor = glm::vec4(r, g, b, a); }
    void setWindowPosition(int x, int y);
    void setWindowSize(int width, int height);
    void setVSync(bool bVSync);

	// get elapsed time when app is running
	float getTime();
    
    glm::ivec2 getMousePosition() const;
    glm::ivec2 getWindowSize() const { return windowSize; }
    glm::ivec2 getWindowPosition() const { return windowPosition; }
    GLFWwindow* getWindow() const { return window; }

    bool isInited() const { return bInit; }
    bool isEnabledVSync() const { return bVSync; }

    struct s3KeyInputState;

private:
    s3Window();
    ~s3Window();

    void render();
    void setCurrentDirectory();

    static void keyInput(GLFWwindow* window);
    static void functionKey(GLFWwindow* window, bool& control, bool& shift, bool& alt);
    static void errorCB(int error, const char* description);
    static void keyCB(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void resizeCB(GLFWwindow* window, int width, int height);
    static void mouseMoveCB(GLFWwindow* window, double xPos, double yPos);
    static void mouseButtonCB(GLFWwindow* window, int button, int action, int mods);
    static void mouseScrollCB(GLFWwindow* window, double xOffset, double yOffset);
    static void windowCloseCB(GLFWwindow* window);
    static void focusCB(GLFWwindow* window, int focused);

    // thread safe
    static s3Window instance;

    bool bInit  = false;
    bool bVSync = true;

    GLFWwindow* window = nullptr;
    glm::ivec2 windowSize     = glm::ivec2();
    glm::ivec2 windowPosition = glm::ivec2();

    glm::vec4 clearColor = glm::vec4();
	s3Timer timer;

    static std::list<s3KeyInputState> keyInputList;
};