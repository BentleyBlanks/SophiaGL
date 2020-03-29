#pragma once
#include <core/s3Settings.h>

class s3Texture
{
public:
	s3Texture(std::string path);
	~s3Texture();

	void begin();
	void end();

	int getWidth() const;
	int getHeight() const;
	int getChannels() const;

	bool isLoaded() const;
	uint32 getTexture() const;

private:
	int32 width    = -1;
	int32 height   = -1;
	int32 channels = -1;

	bool bIsLoaded = false;
	uint32 texture = 0;
};