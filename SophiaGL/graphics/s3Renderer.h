#pragma once
#include <core/s3Settings.h>
#include <glm/glm.hpp>

class s3Window;
class s3Mesh;
class s3Material;
class s3Texture;
class s3RenderTexture;
class s3Renderer
{
public:
    static s3Renderer& getInstance() { return instance; }

    void setDepthTest(bool bDepthTest);
    bool isDepthTest() const { return bDepthTest; }

    void clear(glm::vec4 clearColor, bool color = true, bool depth = true) const;

    void blit(s3Texture& src, s3RenderTexture& dst);
    void blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material);
    void setRenderTarget(const s3RenderTexture& rt);
    void drawMesh(const s3Mesh& mesh, const s3Material& material);

private:
    s3Renderer();
    ~s3Renderer();

    // thread safe
    static s3Renderer instance;
    s3Window& window;

    bool bDepthTest = true;
};