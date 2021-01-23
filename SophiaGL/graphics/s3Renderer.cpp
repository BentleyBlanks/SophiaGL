#include <graphics/s3Renderer.h>
#include <graphics/s3Material.h>
#include <3d/s3Mesh.h>
#include <app/s3Window.h>
#include <glad/glad.h>

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst)
{
}

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material)
{
}

bool s3Renderer::checkRTAndCreated(s3RenderTexture& rt)
{
	if (!rt.isCreated()) rt.create();
	return rt.isCreated();
}

void s3Renderer::setRenderTarget(s3RenderTexture& rt)
{
	if (!checkRTAndCreated(rt)) return;
	
	glBindFramebuffer(GL_FRAMEBUFFER, rt.fbo);
	if(rt.isColorBufferCreated()) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt.colorBuffer.id, 0);
	if(rt.isDepthBufferCreated()) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rt.depthBuffer.id);
}

void s3Renderer::setRenderTarget(s3RenderBuffer& colorBuffers, s3RenderBuffer& depthBuffer)
{
	//if (!checkRTAndCreated(*colorBuffers.rt)) return;
	//if (!checkRTAndCreated(*depthBuffer.rt)) return;

	//glBindFramebuffer(GL_FRAMEBUFFER, colorBuffers.rt->fbo);
	//if (rt.isColorBufferCreated()) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt.colorBuffer.id, 0);
	//if (rt.isDepthBufferCreated()) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rt.depthBuffer.id);
}

void s3Renderer::setRenderTarget(std::vector<s3RenderBuffer>&colorBuffers, s3RenderBuffer & depthBuffer)
{
}

void s3Renderer::clearRenderTarget(bool clearDepth, bool clearColor, glm::vec4 backgroundColor, float depth)
{
	unsigned int mask = 0;
	if (clearColor)
	{
		glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
		mask |= GL_COLOR_BUFFER_BIT;
	}

	if (clearDepth)
	{
		glClearDepth(depth);
		mask |= GL_DEPTH_BUFFER_BIT;
	}
	glClear(mask);
}

void s3Renderer::drawMesh(const s3Mesh& mesh, const s3Material& material)
{
	auto shader = material.getShader();
	shader.begin();

	for (auto submesh : mesh.submeshes)
	{
		if (!submesh->visible) continue;

		// update mesh's vertex stream with shader's inputlayout
		submesh->updateVertexStream(shader.getInputLayoutHandle());

		// draw mesh
		glBindVertexArray(submesh->vao);
		glDrawElements(GL_TRIANGLES, (int)submesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	shader.end();
}
