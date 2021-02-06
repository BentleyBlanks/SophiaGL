#include <graphics/s3Graphics.h>
#include <graphics/s3Material.h>
#include <graphics/s3GfxContext.h>
#include <3d/s3Mesh.h>
#include <app/s3Window.h>
#include <glad/glad.h>

void s3Graphics::clear(glm::vec4 clearColor, bool color, bool depth)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void s3Graphics::blit(s3Texture& src, s3RenderTexture& dst)
{
}

void s3Graphics::blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material)
{
}

bool s3Graphics::checkRTAndCreated(s3RenderTexture& rt)
{
	if (!rt.isCreated()) rt.create();
	return rt.isCreated();
}

void s3Graphics::setRenderTarget(s3RenderTexture& rt)
{
	if (!checkRTAndCreated(rt)) return;
	
	auto frameBuffer = s3GetContext().getFrameBuffer();
	frameBuffer.bind();
	frameBuffer.setAttachments(&rt);

	if(rt.isColorBufferCreated()) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt.colorBuffer.id, 0);
	if(rt.isDepthBufferCreated()) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rt.depthBuffer.id);
}

void s3Graphics::setRenderTarget(s3RenderBuffer& colorBuffers, s3RenderBuffer& depthBuffer)
{
	//if (!checkRTAndCreated(*colorBuffers.rt)) return;
	//if (!checkRTAndCreated(*depthBuffer.rt)) return;

	//glBindFramebuffer(GL_FRAMEBUFFER, colorBuffers.rt->fbo);
	//if (rt.isColorBufferCreated()) glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, rt.colorBuffer.id, 0);
	//if (rt.isDepthBufferCreated()) glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rt.depthBuffer.id);
}

void s3Graphics::setRenderTarget(std::vector<s3RenderBuffer>& colorBuffers, s3RenderBuffer & depthBuffer)
{
}

void s3Graphics::clearRenderTarget(bool clearDepth, bool clearColor, glm::vec4 backgroundColor, float depth)
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

void s3Graphics::drawMesh(const s3Mesh& mesh, const s3Material& material)
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
