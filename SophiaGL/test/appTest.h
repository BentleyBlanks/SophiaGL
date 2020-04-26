#pragma once
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <app/s3CallbackManager.h>
#include <app/s3Window.h>
#include <3d/s3Camera.h>
#include <graphics/s3Renderer.h>
#include <graphics/s3Shader.h>
#include <graphics/s3Texture.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float fov = 45.0f;
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;

// camera
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);

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

class s3App : public s3CallbackHandle
{
public:
    void onHandle(const s3CallbackUserData* userData)
    {
        static auto bFirst = true;

        s3Window& window = s3Window::getInstance();

        if (userData->sender == &s3CallbackManager::onEngineInit)
        {
            camera.position  = glm::vec3(0.0f, 0.0f, 3.0f);
            camera.up        = glm::vec3(0.0f, 1.0f, 0.0f);
            camera.direction = glm::vec3(0.0f, 0.0f, -1.0f);

            texture0.load("../../resources/images/lulu.jpg");
            texture1.load("../../resources/images/lulu2.jpg");
            // could be removed when shader parser added
            texture0.setLocation(0);
            texture1.setLocation(1);

            shader.load("../../SophiaGL/shaders/coordinateVS.glsl", "../../SophiaGL/shaders/coordinateFS.glsl");

            // vao generation and bind
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);

            // vbo generation and bind
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

            s3Renderer::getInstance().setDepthTest(true);
        }
        else if (userData->sender == &s3CallbackManager::onUpdate)
        {
            // time update
            float currentFrame = window.getTime();
            deltaTime = currentFrame - lastFrameTime;
            lastFrameTime = currentFrame;

            // window may resize
            auto windowSize = window.getWindowSize();
            camera.aspectRatio = (float)windowSize.x / windowSize.y;
            camera.speed       = 2.5f * deltaTime;
        }
        else if (userData->sender == &s3CallbackManager::onBeginRender)
        {
            shader.setMatrix("projection", camera.getProjectionMatrix());
            shader.setMatrix("view", camera.getViewMatrix());
            shader.setTexture("texture0", &texture0);
			shader.setTexture("texture1", &texture1);

			// activate shader and clearing
			if (bFirst)
			{
				shader.print();
				bFirst = false;
			}

            // render boxes
            glBindVertexArray(vao);
            for (int i = 0; i < 10; i++)
            {
                float angle = 20.0f * i;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

                shader.setMatrix("model", model);
                shader.begin();

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }
        else if (userData->sender == &s3CallbackManager::onEngineDeinit)
        {

        }
    }

    float deltaTime     = 0.0f;
    float lastFrameTime = 0.0f;

    s3Texture texture0, texture1;
    s3Shader shader;
    s3Camera camera;

    unsigned int vao, vbo;
};

int main()
{
    s3App app;
    s3CallbackManager::onEngineInit  += app;
    s3CallbackManager::onUpdate      += app;
    s3CallbackManager::onBeginRender += app;

    s3Window& window = s3Window::getInstance();
    window.init("SophiaGL", 100, 100, 1280, 720);
    window.run();

    return 0;
}