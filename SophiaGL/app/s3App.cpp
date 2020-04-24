#include <app/s3App.h>
#include <app/s3CallbackManager.h>
#include <core/s3Settings.h>
#include <core/s3Event.h>
#include <core/log/s3Log.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

s3App s3App::instance;

s3App::s3App()
{
    clearColor     = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    windowSize     = glm::ivec2();
    windowPosition = glm::ivec2();
}

s3App::~s3App()
{
}

s3App& s3App::getInstance()
{
    return instance;
}

bool s3App::init(const char* title, int x, int y, int width, int height)
{
    if (width <= 0 || height <= 0) return false;

    s3CallbackInit();

    // init window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        s3Log::error("Failed to create GLFW window/n");
        glfwTerminate();
        return false;
    }
 
    glfwMakeContextCurrent(window);

    // init renderer
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        s3Log::error("Failed to initialize GLAD/n");
        return false;
    }

    setWindowSize(width, height);
    setWindowPosition(x, y);

    // init glfw callback functions
    glfwSetFramebufferSizeCallback(window, resizeCB);
    glfwSetMouseButtonCallback(window, mouseButtonCB);
    glfwSetCursorPosCallback(window, mouseMoveCB);
    glfwSetScrollCallback(window, mouseScrollCB);

    bInit = true;
    return true;
}

float s3App::getTimeElapsed()
{
	timer.end();
	float elapsedTime = (float) timer.difference();
	return elapsedTime;
}

void s3App::shutdown()
{
    s3CallbackDeinit();
    glfwSetWindowShouldClose(window, true);
    //glfwTerminate();
}

void s3App::render()
{
    s3CallbackManager::callBack.onUpdate.trigger();

    glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    s3CallbackManager::callBack.onBeginRender.trigger();
    // renderer draw something
    s3CallbackManager::callBack.onEndRender.trigger();

    // Present
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void s3App::run()
{
    if (!isInited())
    {
        s3Log::warning("s3App need to be called init() first\n");
        return;
    }

    s3CallbackManager::callBack.onEngineInit.trigger();

    while(true)
    {
        input();
        render();
    }
}

void s3App::input()
{
    s3CallbackUserData keyPressData;
    GLFWwindow* window = s3App::getInstance().getWindow();

    // key press event
    for (int i = 0; i < FOO(s3MouseEvent, s3ButtonType).getCount(); i++)
    {
        s3KeyCodeType keyCodeType = FOO(s3KeyEvent, s3CodeType).fromIndex(i);
        if (glfwGetKey(window, (int)s3KeyCodeType::W) == GLFW_PRESS)
        {
            s3KeyTriggerType type = s3KeyTriggerType::pressed;
            s3KeyEvent keyEvent(keyCodeType, type, 0, false, false, false);
            keyPressData.data = (void*)(&keyEvent);
            s3CallbackManager::callBack.onKeyPressed.trigger(&keyPressData);
            break;
        }
    }

    // key release event
	//s3CallbackUserData keyReleaseData;
	//for (int i = 0; i < s3KeyCodeEnumCount; i++)
	//{
	//	if (glfwGetKey(window, s3KeyCodeEnum[i]) == GLFW_RELEASE)
	//	{
	//		s3KeyEvent keyEvent((s3KeyCode)s3KeyCodeEnum[i], 0, false, false, false);
	//		keyReleaseData.data = (void*)(&keyEvent);
	//		s3CallbackManager::callBack.onKeyReleased.trigger(&keyReleaseData);
	//		break;
	//	}
	//}
}

void s3App::setClearColor(float r, float g, float b, float a)
{
    clearColor = glm::vec4(r, g, b, a);
}

void s3App::setWindowPosition(int x, int y)
{
    glfwSetWindowPos(window, x, y);

    windowPosition.x = x;
    windowPosition.y = y;
}

void s3App::setWindowSize(int width, int height)
{
    if (width <= 0 || height <= 0) return;

    windowSize.x = width;
    windowSize.y = height;

    glViewport(0, 0, windowSize.x, windowSize.y);
}

GLFWwindow* s3App::getWindow() const
{
    return window;
}

bool s3App::isInited() const
{
    return bInit;
}

glm::ivec2 s3App::getWindowSize() const
{
    return windowSize;
}

glm::ivec2 s3App::getWindowPosition() const
{
    return windowPosition;
}

void s3App::resizeCB(GLFWwindow* window, int width, int height)
{
    s3App::getInstance().setWindowSize(width, height);
}

void s3App::mouseMoveCB(GLFWwindow* window, double xPos, double yPos)
{
    static bool bFirst = true;
    static float lastX = 400;
    static float lastY = 300;

    float curX = (float)xPos;
    float curY = (float)yPos;

    if (bFirst)
    {
        lastX = curX;
        lastY = curY;
        bFirst = false;
    }

    float xOffset = curX - lastX;
    float yOffset = lastY - curY;

    s3CallbackUserData moveData;
    s3MouseEvent moveEvent(s3MouseButtonType::none, s3MouseTriggerType::none, 0, 0, (int)xOffset, (int)yOffset, 0, false, false);
    moveData.data = (void*)(&moveEvent);
    s3CallbackManager::callBack.onMouseMoved.trigger(&moveData);
}

void s3App::mouseButtonCB(GLFWwindow* window, int button, int action, int mods)
{
    s3MouseButtonType buttonType = s3MouseButtonType::none;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_RIGHT:
        buttonType = s3MouseButtonType::right;
        break;
    case GLFW_MOUSE_BUTTON_LEFT:
        buttonType = s3MouseButtonType::left;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        buttonType = s3MouseButtonType::middle;
        break;
    }

    s3CallbackUserData buttonData;
    s3MouseEvent moveEvent(buttonType, s3MouseTriggerType::none, 0, 0, 0, 0, 0, false, false);
    buttonData.data = (void*)(&moveEvent);
    
    if(action == GLFW_PRESS)
        s3CallbackManager::callBack.onMousePressed.trigger(&buttonData);
    if(action == GLFW_RELEASE)
        s3CallbackManager::callBack.onMouseReleased.trigger(&buttonData);
}

void s3App::mouseScrollCB(GLFWwindow * window, double xOffset, double yOffset)
{
    s3CallbackUserData scrollData;
    s3MouseEvent scrollEvent(s3MouseButtonType::middle, s3MouseTriggerType::none, 0, 0, 0, 0, (float)yOffset, false, false);
    scrollData.data = (void*)(&scrollEvent);
    s3CallbackManager::callBack.onMouseScrolled.trigger(&scrollData);
}

