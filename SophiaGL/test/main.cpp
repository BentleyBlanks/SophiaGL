#include <core/log/s3Log.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>

float vertices[] = 
{
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

const char* vsSource = "#version 330 core\n"
"layout(location = 0) in vec3 PositionWS;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(PositionWS.xyz, 1.0);\n"
"}\0";

const char* fsSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// check shader compile / link result
bool checkShaderResult(uint32 shader, bool isLinkInfo)
{
    int success;
    char infoLog[512];

    if(!isLinkInfo)
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    else
        glGetShaderiv(shader, GL_LINK_STATUS, &success);
    
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        s3Log::error("Error::shader %s failed, %s\n", isLinkInfo ? "compile" : "link", infoLog);
        return false;
    }

    return true;
}

bool checkShaderLinkResult(uint32 shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        s3Log::error("Error::vertex shader compilation failed, %s\n", infoLog);
        return false;
    }
    return true;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "SophiaGL", NULL, NULL);
    if (!window)
    {
        s3Log::error("Failed to create GLFW window/n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        s3Log::error("Failed to initialize GLAD/n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // vertex shader generation
    uint32 vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsSource, NULL);
    glCompileShader(vs);
    if (!checkShaderResult(vs, false)) return 0;

    // fragment shader generation
    uint32 fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsSource, NULL);
    glCompileShader(fs);
    if (!checkShaderResult(fs, false)) return 0;

    uint32 shaderProgram;
    shaderProgram = glCreateProgram();

    // combine shaders into program
    glAttachShader(shaderProgram, vs);
    glAttachShader(shaderProgram, fs);
    glLinkProgram(shaderProgram);
    if (!checkShaderResult(shaderProgram, true)) return 0;

    // clear shaders
    glDeleteShader(vs);
    glDeleteShader(fs);

    // vao generation and bind
    uint32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vbo generation and bind
    uint32 vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // configure and enabled vertex attributes with binded shader layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // unbind vao / vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // activate shader and clearing
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // de-allocate all resources
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}