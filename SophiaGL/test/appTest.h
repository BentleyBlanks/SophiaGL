#pragma once
#include <core/log/s3Log.h>
#include <core/s3Event.h>
#include <core/util/s3UtilsIO.h>
#include <app/s3CallbackManager.h>
#include <app/s3Window.h>
#include <3d/s3Camera.h>
#include <3d/s3Mesh.h>
#include <3d/s3ModelImporter.h>
#include <graphics/s3Renderer.h>
#include <graphics/s3Material.h>
#include <graphics/s3Texture2d.h>

#include <shader.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

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
            dirWatchPaths.push_back("../../thirdparty/fake_unity_shader/src/shader_parser");
            dirWatchPaths.push_back("../../thirdparty/fake_unity_shader/src/shaders");
            shaderDirWatch = new s3UtilsDirectoryWatch();
            //shaderDirWatch->watch("../../thirdparty/fake_unity_shader/src/shader_parser", false);
            shaderDirWatch->watch(dirWatchPaths, false);

            info.api = ShaderGraphicsAPI::OpenGL;
            info.root_path = "../../thirdparty/fake_unity_shader/src/";
            shader_init(info);

            camera = new s3Camera();
            camera->position  = glm::vec3(0.0f, 0.0f, 3.0f);
            camera->up        = glm::vec3(0.0f, 1.0f, 0.0f);
            camera->direction = glm::vec3(0.0f, 0.0f, -1.0f);

            texture0 = new s3Texture2d();
            texture1 = new s3Texture2d();
            texture0->load("../../resources/images/sophia.jpg");
            texture1->load("../../resources/images/lulu2.jpg");
            // could be removed when shader parser added
            texture0->setLocation(0);
            texture1->setLocation(1);

            shader = new s3Shader();
            shader->load("./shaders/mainFuckTexture.shader");

            // replaced by Shader::find() in the future
            material = new s3Material(*shader);

            //mesh = s3ModelImporter::load("../../resources/models/sponza/sponza.obj");
            //mesh = s3ModelImporter::load("../../resources/models/cornellBox/CornellBox-Sphere.obj");
            //mesh = s3ModelImporter::load("../../resources/models/cornellBox/water.obj");
            mesh = s3ModelImporter::load("../../resources/models/cube/cube.obj");

            s3Renderer::setDepthTest(true);
        }
        else if (userData->sender == &s3CallbackManager::onUpdate)
        {
            if (shaderDirWatch->hasChanged())
            {
                // hotreload
                shader_init(info);
                shader->reload();
                printf("-----------------------------------------------------------------------\n");
            }

            // time update
            float currentFrame = window.getTime();
            deltaTime = currentFrame - lastFrameTime;
            lastFrameTime = currentFrame;

            // window may resize
            auto windowSize = window.getWindowSize();
            camera->aspectRatio = (float)windowSize.x / windowSize.y;
            camera->speed       = cameraSpeed * deltaTime;
        }
        else if (userData->sender == &s3CallbackManager::onBeginRender)
        {
            ImGui::Begin("Sophia");
            ImGui::Text("Camera");
            ImGui::DragFloat("Speed", &cameraSpeed, 1.0f, 0.0f, 200.0f);
            ImGui::DragFloat("Near Plane", &camera->nearClip, 1.0f, 0.1f, 10.0f);
            ImGui::DragFloat("Far Plane", &camera->farClip, 1.0f, 0.0f, 100000.0f);
            ImGui::DragFloat("FOV", &camera->fov, 1.0f, 1.0f, 180.0f);
            ImGui::DragFloat3("Position", &camera->position.x, 1.0f, -10000.0f, 10000.0f);
            ImGui::DragFloat3("Direction", &camera->direction.x, 1.0f, -1.0f, 1.0f);
            ImGui::Separator();

            ImGui::Text("Vertex Shader");
            ImGui::Text(shader->getVertexSource().c_str());
            ImGui::Separator();
            ImGui::Text("Fragment Shader");
            ImGui::Text(shader->getFragmentSource().c_str());

            ImGui::Separator();

            if (ImGui::Button("Print", ImVec2(ImGui::GetWindowSize().x, 0)))
            {
                shader->print();
            }
            ImGui::End();

            material->setTexture("texture0", texture0);
            //material->setTexture("texture1", texture1);

            material->setDouble3("fuckGLSL0", glm::dvec3(-2, 3, 4));
            material->setDouble3("fuckGLSL1", glm::dvec3(-2, 3, 4));
            material->setDouble1("fuckDouble0", glm::dvec1(3.1415));
            material->setDouble1("fuckDouble1", glm::dvec1(3.1415));
            material->setFloat3("testValue0", glm::vec3(-5.0f, 6.0f, -7.0f));
            material->setBool1("testValue1", glm::bvec1(true));
            material->setFloat1("testFloat", glm::vec1(15.0f));

            auto projectionMat = camera->getProjectionMatrix();
            auto viewMat       = camera->getViewMatrix();
            material->setMatrix4("projection", projectionMat);
            material->setMatrix4("view", viewMat);
			// activate shader and clearing
			if (bFirst)
			{
                material->print();
				bFirst = false;
			}

            // render boxes
            s3Renderer::setDepthTest(true);
            for (int i = 0; i < 1; i++)
            {
                float angle = 20.0f * i;

                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, cubePositions[i]);
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

                material->setMatrix4("model", model);
                s3Renderer::drawMesh(*mesh, *material);
            }
        }
        else if (userData->sender == &s3CallbackManager::onEngineDeinit)
        {
            S3_SAFE_DELETE(camera);
            S3_SAFE_DELETE(texture0);
            S3_SAFE_DELETE(texture1);
            S3_SAFE_DELETE(material);
            S3_SAFE_DELETE(shader);
            S3_SAFE_DELETE(mesh);
            S3_SAFE_DELETE(shaderDirWatch);
        }
        else if (userData->sender == &s3CallbackManager::onWindowFocused)
        {
            if (shaderDirWatch->hasChanged())
                shader->reload();
        }
    }

    float deltaTime     = 0.0f;
    float lastFrameTime = 0.0f;
    float cameraSpeed   = 2.5f;

    s3Texture2d* texture0                 = nullptr;
    s3Texture2d *texture1                 = nullptr;
    s3Shader *shader                      = nullptr;
    s3Material* material                  = nullptr;
    s3Camera *camera                      = nullptr;
    s3Mesh* mesh                          = nullptr;
    s3UtilsDirectoryWatch* shaderDirWatch = nullptr;

    ShaderInitInfo info;
    std::vector<std::string> dirWatchPaths;

    unsigned int vao = 0, vbo = 0;
};

int main()
{
    s3App app;
    s3CallbackManager::onEngineInit    += app;
    s3CallbackManager::onUpdate        += app;
    s3CallbackManager::onBeginRender   += app;
    s3CallbackManager::onWindowFocused += app;

    s3Window& window = s3Window::getInstance();
    window.init("SophiaGL", 100, 100, 1280, 720);
    window.run();

     return 0;
}