#include <app/s3Window.h>
#include <app/s3CallbackManager.h>
#include <core/s3Settings.h>
#include <core/s3Event.h>
#include <core/log/s3Log.h>
#include <graphics/s3Renderer.h>

#include <glad/glad.h>
#include <glfw/glfw3.h>

struct s3Window::s3KeyInputState
{
    s3KeyType key;
    s3KeyTriggerType triggerType;
};

s3Window s3Window::instance;
std::list<s3Window::s3KeyInputState> s3Window::keyInputList;

s3Window::s3Window() : renderer(s3Renderer::getInstance())
{
    clearColor     = glm::vec4(0.2f, 0.3f, 0.3f, 1.0f);
    windowSize     = glm::ivec2();
    windowPosition = glm::ivec2();
}

s3Window::~s3Window()
{
}

bool s3Window::init(const char* title, int x, int y, int width, int height)
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
    glfwSetKeyCallback(window, keyCB);
    glfwSetWindowCloseCallback(window, windowCloseCB);

    s3CallbackManager::onEngineInit.trigger();

    bInit = true;
    return true;
}

float s3Window::getTime()
{
    return (float)glfwGetTime();
}

void s3Window::shutdown()
{
    s3CallbackDeinit();
    glfwSetWindowShouldClose(window, true);
    glfwTerminate();
}

void s3Window::render()
{
    renderer.clear(clearColor);

    s3CallbackManager::onBeginRender.trigger();
    // renderer draw something
    s3CallbackManager::onEndRender.trigger();

    // Present
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void s3Window::functionKey(GLFWwindow* window, bool& control, bool& shift, bool& alt)
{
    control = false;
    shift   = false;
    alt     = false;

    if (glfwGetKey(window, (int)s3KeyType::leftAlt) == GLFW_PRESS ||
        glfwGetKey(window, (int)s3KeyType::rightAlt) == GLFW_PRESS)
        alt = true;

    if (glfwGetKey(window, (int)s3KeyType::leftControl) == GLFW_PRESS ||
        glfwGetKey(window, (int)s3KeyType::rightControl) == GLFW_PRESS)
        control = true;

    if (glfwGetKey(window, (int)s3KeyType::leftShift) == GLFW_PRESS ||
        glfwGetKey(window, (int)s3KeyType::rightShift) == GLFW_PRESS)
        shift = true;
}

void s3Window::run()
{
    if (!isInited())
    {
        s3Log::warning("s3Window need to be called init() first\n");
        return;
    }

    // render loop
    while(!glfwWindowShouldClose(window))
    {
        s3CallbackManager::onUpdate.trigger();

        keyInput(window);
        render();
    }
}

void s3Window::keyInput(GLFWwindow* window)
{
	bool control = false, shift = false, alt = false;
	functionKey(window, control, shift, alt);

	for (auto it = keyInputList.begin(); it != keyInputList.end(); )
	{
		auto keyType        = it->key;
        auto triggerType    = it->triggerType;
		auto keyCode        = s3EnumUtil(s3KeyType).toString(keyType);
		auto triggerTypeStr = s3EnumUtil(s3KeyTriggerType).toString(triggerType);
        //s3Log::debug("keyType: %d, triggerType: %s\n", (int)keyType, triggerTypeStr.c_str());

		s3CallbackUserData userData;
		s3KeyEvent keyEvent(keyType, triggerType, keyCode, control, shift, alt);
		userData.data = (void*)(&keyEvent);

        if (triggerType == s3KeyTriggerType::pressed)
        {
            // delete until key released
            s3CallbackManager::onKeyPressed.trigger(&userData);
            it++;
        }
        else
        {
            // only process release event once
            s3CallbackManager::onKeyReleased.trigger(&userData);
            it = keyInputList.erase(it);
        }
	}
}

// key repeat triggered after N frames, so put keyEvent message into GameLoop
void s3Window::keyCB(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto keyType = (s3KeyType)key;
    auto keyCode = s3EnumUtil(s3KeyType).toString(keyType);

    bool pressed  = action == GLFW_PRESS;
    bool released = action == GLFW_RELEASE;
    bool repeat   = action == GLFW_REPEAT;
    
    // make the key pressed message unique
    s3Window::s3KeyInputState state;
    state.key         = (s3KeyType)key;
    state.triggerType = s3KeyTriggerType::pressed;
    auto it = std::find_if(keyInputList.begin(), keyInputList.end(), [state](const s3KeyInputState _state)
    {
        return (state.key == _state.key) && (state.triggerType == _state.triggerType);
    });

    if (pressed || repeat)
    {
        if (it == keyInputList.end())
            keyInputList.push_back(state);
        //else
        //    s3Log::debug("Key: %s already pressed\n", keyCode.c_str());
    }
    else if (released)
    {
        if (it != keyInputList.end())
            it->triggerType = s3KeyTriggerType::released;
        else
            s3Log::warning("Key: %s released without pressed\n", keyCode.c_str());
    }
}

void s3Window::setWindowPosition(int x, int y)
{
    glfwSetWindowPos(window, x, y);

    windowPosition.x = x;
    windowPosition.y = y;
}

void s3Window::setWindowSize(int width, int height)
{
    if (width <= 0 || height <= 0) return;

    windowSize.x = width;
    windowSize.y = height;

    glViewport(0, 0, windowSize.x, windowSize.y);
}

glm::ivec2 s3Window::getMousePosition() const
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    
    return glm::ivec2((int)xPos, (int)yPos);
}

void s3Window::resizeCB(GLFWwindow* window, int width, int height)
{
    s3Window::getInstance().setWindowSize(width, height);
}

void s3Window::mouseMoveCB(GLFWwindow* window, double xPos, double yPos)
{
    static bool bFirst = true;
    static float lastX = 0.0f;
    static float lastY = 0.0f;

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
    lastX = curX;
    lastY = curY;

    auto mouseType = s3MouseType::none;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        mouseType = s3MouseType::left;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        mouseType = s3MouseType::right;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
        mouseType = s3MouseType::middle;

    bool control = false, shift = false, alt = false;
    functionKey(window, control, shift, alt);

    s3CallbackUserData moveData;
    s3MouseEvent moveEvent(mouseType, s3MouseTriggerType::move, (int)xPos, (int)yPos, (int)xOffset, (int)yOffset, 0, control, shift, alt);
    moveData.data = (void*)(&moveEvent);
    s3CallbackManager::onMouseMoved.trigger(&moveData);
}

void s3Window::mouseButtonCB(GLFWwindow* window, int button, int action, int mods)
{
    auto buttonType = s3MouseType::none;
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_RIGHT:
        buttonType = s3MouseType::right;
        break;
    case GLFW_MOUSE_BUTTON_LEFT:
        buttonType = s3MouseType::left;
        break;
    case GLFW_MOUSE_BUTTON_MIDDLE:
        buttonType = s3MouseType::middle;
        break;
    }

    glm::ivec2 pos = s3Window::getInstance().getMousePosition();

    bool control = false, shift = false, alt = false;
    functionKey(window, control, shift, alt);

    s3CallbackUserData buttonData;
    if (action == GLFW_PRESS)
    {
        s3MouseEvent moveEvent(buttonType, s3MouseTriggerType::pressed, pos.x, pos.y, 0, 0, 0.0f, control, shift, alt);
        buttonData.data = (void*)(&moveEvent);
        s3CallbackManager::onMousePressed.trigger(&buttonData);
    }
    if (action == GLFW_RELEASE)
    {
        s3MouseEvent moveEvent(buttonType, s3MouseTriggerType::released, pos.x, pos.y, 0, 0, 0.0f, control, shift, alt);
        buttonData.data = (void*)(&moveEvent);
        s3CallbackManager::onMouseReleased.trigger(&buttonData);
    }
}

void s3Window::mouseScrollCB(GLFWwindow * window, double xOffset, double yOffset)
{
    s3CallbackUserData scrollData;
    s3MouseEvent scrollEvent(s3MouseType::middle, s3MouseTriggerType::scroll, 0, 0, 0, 0, (float)yOffset, false, false, false);
    scrollData.data = (void*)(&scrollEvent);
    s3CallbackManager::onMouseScrolled.trigger(&scrollData);
}

void s3Window::windowCloseCB(GLFWwindow* window)
{
}

