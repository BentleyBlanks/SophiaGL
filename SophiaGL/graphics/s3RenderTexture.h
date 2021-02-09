#pragma once
#include <graphics/s3Texture.h>

s3Enum(s3RenderTextureFormat,
	   ARGB32,					//  Color render texture format, 8 bits per channel.	
	   Depth,					//  A depth render texture format.	
	   ARGBHalf,				//  Color render texture format, 16 bit floating point per channel.		
	   Shadowmap,				//  A native shadowmap render texture format.		
	   RGB565,					//  Color render texture format.	
	   ARGB4444,				//  Color render texture format, 4 bit per channel.		
	   ARGB1555,				//  Color render texture format, 1 bit for Alpha channel, 5 bits for Red, Green and Blue channels.		
	   Default,					//  Default color render texture format: will be chosen accordingly to Frame Buffer format and Platform.	
	   ARGB2101010,				//  Color render texture format. 10 bits for colors, 2 bits for alpha.		
	   DefaultHDR,				//  Default HDR color render texture format: will be chosen accordingly to Frame Buffer format and Platform.		
	   ARGB64,					//  Four color render texture format, 16 bits per channel, fixed point, unsigned normalized.	
	   ARGBFloat,				//  Color render texture format, 32 bit floating point per channel.		
	   RGFloat,					//  Two color (RG) render texture format, 32 bit floating point per channel.	
	   RGHalf,					//  Two color (RG) render texture format, 16 bit floating point per channel.	
	   RFloat,					//  Scalar (R) render texture format, 32 bit floating point.	
	   RHalf,					//  Scalar (R) render texture format, 16 bit floating point.	
	   R8,						//  Single channel (R) render texture format, 8 bit integer.
	   ARGBInt,					//  Four channel (ARGB) render texture format, 32 bit signed integer per channel.	
	   RGInt,					//  Two channel (RG) render texture format, 32 bit signed integer per channel.	
	   RInt,					//  Scalar (R) render texture format, 32 bit signed integer.	
	   BGRA32,					//  Color render texture format, 8 bits per channel.	
	   RGB111110Float,			//  Color render texture format. R and G channels are 11 bit floating point, B channel is 10 bit floating point.			
	   RG32,					//  Two color (RG) render texture format, 16 bits per channel, fixed point, unsigned normalized.	
	   RGBAUShort,				//  Four channel (RGBA) render texture format, 16 bit unsigned integer per channel.		
	   RG16,					//  Two channel (RG) render texture format, 8 bits per channel.	
	   BGRA10101010_XR,			//  Color render texture format, 10 bit per channel, extended range.			
	   BGR101010_XR,			//  Color render texture format, 10 bit per channel, extended range.			
	   R16						//  Single channel (R) render texture format, 16 bit integer.
);

//class s3RenderTextureDescriptor
//{
//public:
//	//bool autoGenerateMips;
//	//bool bindMS;
//	unsigned int depthBufferBits;
//	s3TextureDimension dimension;
//	//enableRandomWrite;
//	//flags;
//	s3RenderTextureFormat graphicsFormat;
//	unsigned int height;
//	//memoryless;
//	//unsigned int mipmapCount;
//	//msaaSamples;
//	//shadowSamplingMode;
//	//sRGB;
//	//stencilFormat;
//	//useDynamicScale;
//	//bool useMipMap;
//	//volumeDepth;
//	//vrUsage;
//	unsigned int width;
//};

class s3RenderTexture;
class s3RenderBuffer
{
public:
	unsigned int id = 0;
	s3RenderTexture* rt = nullptr;
};

class s3FrameBuffer
{
public:
	s3FrameBuffer() {}
	~s3FrameBuffer();

	void create();
	void release();
	bool isCreated() const { return bIsCreated; }

	void bind();
	void unbind();

	void setAttachments(s3RenderTexture* attachment) { renderTextureAttachment = attachment; }
	void setAttachments(s3RenderBuffer* attachment0, s3RenderBuffer* attachment1) { colorBufferAttachment = attachment0; depthBufferAttachment = attachment1; }

private:
	bool bIsCreated = false;
	
	unsigned int id = 0;
	s3RenderTexture* renderTextureAttachment = nullptr;
	s3RenderBuffer* colorBufferAttachment    = nullptr;
	s3RenderBuffer* depthBufferAttachment    = nullptr;
};

class s3RenderTexture : public s3Texture
{
public:
	s3RenderTexture(int width, int height, int depth, s3RenderTextureFormat format = s3RenderTextureFormat::Default);
	~s3RenderTexture();

	bool create();
	void release();

	bool isCreated() const { return bIsCreated; }
	bool isColorBufferCreated() const { return bIsColorBufferCreated; }
	bool isDepthBufferCreated() const { return bIsDepthBufferCreated; }

	s3RenderBuffer colorBuffer;
	s3RenderBuffer depthBuffer;

	// When 0 is used, then no Z buffer is created by a render texture.
	unsigned int depthBufferBits = 0;
	s3RenderTextureFormat format = s3RenderTextureFormat::Default;

protected:
	bool bIsCreated            = false;
	bool bIsColorBufferCreated = false;
	bool bIsDepthBufferCreated = false;
};