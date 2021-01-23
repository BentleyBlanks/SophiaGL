#pragma once
#include <core/s3Settings.h>
#include <graphics/s3RenderTexture.h>
#include <glm/glm.hpp>

class s3Window;
class s3Mesh;
class s3Material;
class s3Renderer
{
public:
    static void blit(s3Texture& src, s3RenderTexture& dst);
    static void blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material);

    // rt would be created if not created yet
    static void setRenderTarget(s3RenderTexture& rt);
    static void setRenderTarget(s3RenderBuffer& colorBuffers, s3RenderBuffer& depthBuffer);
    static void setRenderTarget(std::vector<s3RenderBuffer>& colorBuffers, s3RenderBuffer& depthBuffer);

    static void clearRenderTarget(bool clearDepth, bool clearColor, glm::vec4 backgroundColor, float depth = 1.0f);
    
    static void drawMesh(const s3Mesh& mesh, const s3Material& material);
private:
    static bool checkRTAndCreated(s3RenderTexture& rt);
};