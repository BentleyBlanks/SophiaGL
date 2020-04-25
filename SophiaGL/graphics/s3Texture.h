#pragma once
#include <core/s3Settings.h>

class s3Texture
{
public:
	s3Texture();
	s3Texture(const char* path);
	~s3Texture();

	void begin();
	void end();

	int getWidth() const;
	int getHeight() const;
	int getChannels() const;

	bool load(const char* path);
	bool isLoaded() const;
	unsigned int getTexture() const;

private:
	int width    = -1;
	int height   = -1;
	int channels = -1;

	bool bIsLoaded = false;
	unsigned int texture = 0;
};