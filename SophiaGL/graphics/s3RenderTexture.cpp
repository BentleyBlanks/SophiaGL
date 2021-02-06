#include <graphics/s3RenderTexture.h>
#include <glad/glad.h>

// -------------------------------------------s3FrameBuffer-------------------------------------------
s3FrameBuffer::~s3FrameBuffer()
{
	release();
}

void s3FrameBuffer::create()
{
	glGenFramebuffers(1, &id);
	bIsCreated = true;
}

void s3FrameBuffer::release()
{
	glDeleteFramebuffers(1, &id);
	id = 0;
	bIsCreated = false;
}

void s3FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
}

void s3FrameBuffer::unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// -------------------------------------------s3RenderTexture-------------------------------------------
//--! ref: https://docs.unity3d.com/ScriptReference/RenderTexture.html
s3RenderTexture::s3RenderTexture(int width, int height, int depth, s3RenderTextureFormat format)
{
	this->width           = width;
	this->height          = height; 
	this->format          = format;
	this->depthBufferBits = depth;
}

s3RenderTexture::~s3RenderTexture()
{
	release();
}

bool s3RenderTexture::create()
{
	if (bIsCreated) return true;

	colorBuffer.rt = this;
	depthBuffer.rt = this;

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

		bIsColorBufferCreated = true;
	}

	// generate depth texture attachment if needed
	if (depthBufferBits > 0)
	{
		glGenRenderbuffers(1, &depthBuffer.id);
		glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer.id);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		bIsDepthBufferCreated = true;
	}

	if (colorBuffer.id == 0 ||
		depthBuffer.id == 0 ||
		glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		bIsColorBufferCreated = false;
		bIsDepthBufferCreated = false;
		s3Log::error("s3RenderTexture: %s created failed", name.c_str());
	}
	
	bIsCreated = true;
	return true;
}

void s3RenderTexture::release()
{
	glDeleteTextures(1, &colorBuffer.id);
	glDeleteRenderbuffers(1, &depthBuffer.id);

	colorBuffer.id = 0;
	depthBuffer.id = 0;
	bIsCreated     = false;
}
