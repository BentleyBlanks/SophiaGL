#pragma once
#include <core/s3Settings.h>
#include <glm/glm.hpp>

class s3Window;
class s3Renderer
{
public:
    static s3Renderer& getInstance();

    void setDepthTest(bool bDepthTest);
    bool isDepthTest() const;

    void clear(glm::vec4 clearColor, bool color = true, bool depth = true) const;

private:
    s3Renderer();
    ~s3Renderer();

    // thread safe
    static s3Renderer instance;
    s3Window& window;

    bool bDepthTest = true;
};