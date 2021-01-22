#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>

s3Enum(s3TextureWarpMode,
	   repeat,	    // Tiles the texture, creating a repeating pattern.
	   clamp,	    // Clamps the texture to the last pixel at the edge.
	   mirror,	    // Tiles the texture, creating a repeating pattern by mirroring it at every integer boundary.
	   mirrorOnce	// Mirrors the texture once, then clamps to edge pixels.
);

s3Enum(s3TextureFilterMode,
	   point,		// Point filtering - texture pixels become blocky up close.
	   bilinear,	// Bilinear filtering - texture samples are averaged.
	   trilinear	// Trilinear filtering - texture samples are averaged and also blended between mipmap levels.
);

s3Enum(s3TextureDimension,
	   unknown,		// Texture type is not initialized or unknown.
	   none,		// No texture is assigned.
	   any,			// Any texture type.
	   tex2D,		// 2D texture (Texture2D).
	   tex3D,		// 3D volume texture (Texture3D).
	   cube,		// Cubemap texture.
	   tex2DArray,	// 2D array texture (Texture2DArray).
	   cubeArray,	// Cubemap array texture (CubemapArray).
);

class s3Texture
{
public:
	s3Texture() {}
	~s3Texture() {}

	//int getWidth() const { return width; }
	//int getHeight() const { return height; }
	//int getChannels() const { return channels; }
	//int getMipCount() const { return mipCount; }

	//s3WarpMode getWarpMode() const { return warpMode; }
	//s3TextureFormat getTextureFormat() const { return format; }
	unsigned int getTextureID() const { return textureID; }

	// texture properties
	int width       = -1;
	int height      = -1;
	//int channels    = -1;
	//int mipmapCount = 0;
	//int mipmapBias  = 0;

	std::string name = "";

	s3TextureFilterMode filterMode = s3TextureFilterMode::bilinear;
	s3TextureWarpMode warpMode     = s3TextureWarpMode::clamp;
	s3TextureDimension dimension   = s3TextureDimension::tex2D;

protected:
	// opengl render data
	unsigned int textureID = 0;
};