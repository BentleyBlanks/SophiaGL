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
    static void clear(glm::vec4 clearColor, bool color = true, bool depth = true);
    static void blit(s3Texture& src, s3RenderTexture& dst);
    static void blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material);
    static void setRenderTarget(const s3RenderTexture& rt);
    static void drawMesh(const s3Mesh& mesh, const s3Material& material);
private:
};