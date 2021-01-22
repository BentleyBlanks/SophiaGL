#include <graphics/s3RenderTexture.h>
#include <glad/glad.h>

//--! ref: https://docs.unity3d.com/ScriptReference/RenderTexture.html
s3RenderTexture::s3RenderTexture(int width, int height, int depth, s3RenderTextureFormat format)
{
	this->width           = width;
	this->height          = height; 
	this->format          = format;
	this->depthBufferBits = depth;
}

bool s3RenderTexture::create()
{
	if (bIsCreated) return true;

	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// generate color texture attachment
	if (format != s3RenderTextureFormat::Depth ||
		format != s3RenderTextureFormat::Shadowmap)
	{
		glGenTextures(1, &colorBuffer.id);
		glBindTexture(GL_TEXTURE_2D, colorBuffer.id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer.id, 0);
	}

	// generate depth texture attachment if needed
	if (depthBufferBits > 0)
	{
		glGenRenderbuffers(1, &depthBuffer.id);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer.id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer.id);
	}

	if (colorBuffer.id == 0 ||
		depthBuffer.id == 0 ||
		glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		s3Log::error("s3RenderTexture: %s created failed", name.c_str());
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	bIsCreated = true;
	return true;
}

void s3RenderTexture::release()
{
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &colorBuffer.id);
	glDeleteRenderbuffers(1, &depthBuffer.id);

	fbo            = 0;
	colorBuffer.id = 0;
	depthBuffer.id = 0;
	bIsCreated     = false;
}
