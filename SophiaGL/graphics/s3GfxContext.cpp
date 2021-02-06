#include <graphics/s3GfxContext.h>

s3GfxContext g_context;

s3GfxContext& s3GetContext()
{
	return g_context;
}

s3GfxContext::s3GfxContext() {}

s3GfxContext::~s3GfxContext()
{
	if (frameBuffer.isCreated()) frameBuffer.release();
}

s3FrameBuffer& s3GfxContext::getFrameBuffer()
{
	// created the framebuffer only on the first use
	if (!frameBuffer.isCreated()) frameBuffer.create();
	return frameBuffer;
}
