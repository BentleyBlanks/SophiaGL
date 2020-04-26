#pragma once
#include <core/s3Settings.h>

class s3Texture
{
public:
	s3Texture();
	s3Texture(const char* path);
	~s3Texture();

	//void begin(int location);
	//void end(int location);

	// could be removed when shader parser added
	void setLocation(int location);

	int getWidth() const;
	int getHeight() const;
	int getChannels() const;
	int getLocation() const;

	bool load(const char* path);
	bool isLoaded() const;
	unsigned int getTextureID() const;

private:
	int width    = -1;
	int height   = -1;
	int channels = -1;
	int location = 0;

	bool bIsLoaded = false;
	unsigned int textureID = 0;
};