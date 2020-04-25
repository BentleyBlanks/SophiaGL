#include <graphics/s3Renderer.h>
#include <app/s3Window.h>
#include <glad/glad.h>

s3Renderer s3Renderer::instance;

s3Renderer::s3Renderer() : window(s3Window::getInstance())
{}

s3Renderer::~s3Renderer()
{}

s3Renderer& s3Renderer::getInstance()
{
	return instance;
}

void s3Renderer::setDepthTest(bool bDepthTest)
{
	this->bDepthTest = bDepthTest;

	if (bDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

bool s3Renderer::isDepthTest() const
{
	return bDepthTest;
}

void s3Renderer::clear(glm::vec4 clearColor, bool color, bool depth) const
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}