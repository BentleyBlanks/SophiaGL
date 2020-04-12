#pragma once
#include <core/log/s3Log.h>
//#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <graphics/s3Shader.h>
#include <graphics/s3Texture.h>

float width = 800.0f;
float height = 600.0f;

//float vertices[] =
//{
//    // positions          // colors           // texture coords
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
//};

float vertices[] = 
{
    // positions          // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

glm::vec3 cubePositions[] = 
{
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        s3Log::error("Failed to initialize GLAD/n");
        return -1;
    }

    glViewport(0, 0, (int)width, (int)height);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    s3Texture texture0("../../resources/images/lulu.jpg");
    s3Texture texture1("../../resources/images/lulu2.jpg");
    if (!texture0.isLoaded()) return 0;
    if (!texture1.isLoaded()) return 0;

    s3Shader shader("../../SophiaGL/shaders/coordinateVS.glsl", "../../SophiaGL/shaders/coordinateFS.glsl");
    if (!shader.isLoaded()) return 0;

    // vao generation and bind
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // vbo generation and bind
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // configure and enabled vertex attributes, and binded shader layout
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // unbind vao / vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // camera
    //glm::vec3 up           = glm::vec3(0.0f, 1.0f, 0.0f);
    //glm::vec3 cameraPos    = glm::vec3(0.0f, 0.0f, 3.0f);
    //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);

    //glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
    //glm::vec3 cameraRight     = glm::normalize(glm::cross(up, cameraDirection));
    //glm::vec3 cameraUp        = glm::cross(cameraDirection, cameraRight);

    //glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
    //                             glm::vec3(0.0f, 0.0f, 0.0f),
    //                             glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);


    // render loop
    glEnable(GL_DEPTH_TEST);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // camera / view transformation
        float radius = 10.0f;
        float camX   = sin((float)glfwGetTime() * 0.5f) * radius;
		float camZ   = cos((float)glfwGetTime() * 0.5f) * radius;
		glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
									 glm::vec3(0.0f, 0.0f, 0.0f),
									 glm::vec3(0.0f, 1.0f, 0.0f));

        // activate shader and clearing
        shader.begin();
        shader.setMatrix("projection", projection);
        shader.setMatrix("view", view);
        shader.setTexture("texture0", 0);
        shader.setTexture("texture1", 1);

        // textures bind
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0.getTexture());
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture1.getTexture());

        // render boxes
        glBindVertexArray(vao);
        for (int i = 0; i < 10; i++)
        {
            float angle = 20.0f * i;

			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            shader.setMatrix("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    shader.end();

    // de-allocate all resources
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    glfwTerminate();
    return 0;
}