#pragma once
#include <graphics/s3Texture.h>

class s3Texture2d : public s3Texture
{
public:
	s3Texture2d() {}
	s3Texture2d(const char* path) { load(path); }
	~s3Texture2d() {}

	bool load(const char* path);
	bool isLoaded() const { return bIsLoaded; }

	// a small texture with custom color
	static s3Texture2d blackTexture;
	static s3Texture2d whiteTexture;
	static s3Texture2d grayTexture;

private:
	bool bIsLoaded = false;

	//s3TextureFormat format;
};