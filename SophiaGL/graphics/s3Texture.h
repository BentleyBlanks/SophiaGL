#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>

s3Enum(s3WarpMode,
	   repeat = 0,
	   clamp,
	   mirror,
	   mirrorOnce
);

s3Enum(s3TextureFormat,

);

class s3Texture
{
public:
	s3Texture() {}
	~s3Texture() {}

	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getChannels() const { return channels; }
	int getMipCount() const { return mipCount; }

	s3WarpMode getWarpMode() const { return warpMode; }
	s3TextureFormat getTextureFormat() const { return format; }
	unsigned int getTextureID() const { return textureID; }

protected:
	// texture properties
	int width    = -1;
	int height   = -1;
	int channels = -1;
	int mipCount = 0;

	s3WarpMode warpMode = s3WarpMode::clamp;
	s3TextureFormat format;

	// opengl render data
	unsigned int textureID = 0;
};