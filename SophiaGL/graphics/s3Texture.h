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
	s3Texture();
	s3Texture(const char* path);
	~s3Texture();

	// could be removed when shader parser added
	void setLocation(int location);

	int getWidth() const;
	int getHeight() const;
	int getChannels() const;
	int getLocation() const;
	int getMipCount() const;

	s3WarpMode getWarpMode() const;
	s3TextureFormat getTextureFormat() const;

	bool load(const char* path);
	bool isLoaded() const;
	unsigned int getTextureID() const;

private:
	// texture properties
	int width    = -1;
	int height   = -1;
	int channels = -1;
	int mipCount = 0;

	s3WarpMode warpMode;
	s3TextureFormat format;

	bool bIsLoaded = false;
	
	// opengl render data
	unsigned int textureID = 0;
	int location = 0;
};