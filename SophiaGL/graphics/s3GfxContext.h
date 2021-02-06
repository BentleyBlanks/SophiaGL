#pragma once
#include <core/util/s3NonCopyable.h>
#include <graphics/s3RenderTexture.h>

class s3GfxContext
{
public:
	s3GfxContext();
	~s3GfxContext();

	s3FrameBuffer& getFrameBuffer();

private:
	// shared fbo + reattch, separatethe rt and fbo
	s3FrameBuffer frameBuffer;
};

extern s3GfxContext g_context;
s3GfxContext& s3GetContext();