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
	unsigned int getTexture() const;

private:
	int width    = -1;
	int height   = -1;
	int channels = -1;

	bool bIsLoaded = false;
	unsigned int texture = 0;
};