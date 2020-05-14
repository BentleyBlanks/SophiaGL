#include <graphics/s3Renderer.h>
#include <graphics/s3Material.h>
#include <app/s3Window.h>
#include <glad/glad.h>

s3Renderer s3Renderer::instance;

s3Renderer::s3Renderer() : window(s3Window::getInstance())
{}

s3Renderer::~s3Renderer()
{}

void s3Renderer::setDepthTest(bool bDepthTest)
{
	this->bDepthTest = bDepthTest;

	if (bDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void s3Renderer::clear(glm::vec4 clearColor, bool color, bool depth) const
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst)
{
}

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material)
{
}

void s3Renderer::setRenderTarget(const s3RenderTexture& rt)
{
}

void s3Renderer::drawMesh(const s3Mesh& mesh, const s3Material& material)
{

}
