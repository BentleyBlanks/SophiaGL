#include <app/s3Utils.h>
//#include <graphics/s3Renderer.h>
#include <core/log/s3Log.h>

#include <iostream>  
#include <sstream>
#include <iomanip>
#include <iterator>
#include <codecvt>

//std::string s3MouseTypeToString(s3MouseEvent::s3MouseType type)
//{
//    switch (type)
//    {
//    case s3MouseEvent::none:
//        return "None";
//    case s3MouseEvent::left:
//        return "Left";
//    case s3MouseEvent::middle:
//        return "Middle";
//    case s3MouseEvent::right:
//        return "Right";
//    default:
//        return "Unknown";
//    }
//}

//std::string s3GetLatestProfilePixelShader(D3D_FEATURE_LEVEL featureLevel)
//{
//    switch(featureLevel)
//    {
//    case D3D_FEATURE_LEVEL_11_1:
//    case D3D_FEATURE_LEVEL_11_0:
//    {
//        return "ps_5_0";
//    }
//    break;
//    case D3D_FEATURE_LEVEL_10_1:
//    {
//        return "ps_4_1";
//    }
//    break;
//    case D3D_FEATURE_LEVEL_10_0:
//    {
//        return "ps_4_0";
//    }
//    break;
//    case D3D_FEATURE_LEVEL_9_3:
//    {
//        return "ps_4_0_level_9_3";
//    }
//    break;
//    case D3D_FEATURE_LEVEL_9_2:
//    case D3D_FEATURE_LEVEL_9_1:
//    {
//        return "ps_4_0_level_9_1";
//    }
//    break;
//    }
//    return "";
//}

s3ImageType s3GetImageType(const std::string & filePath)
{
    s3ImageType type;
    char extension[32];
    _splitpath(filePath.c_str(), NULL, NULL, NULL, extension);

    // parsing image file's postfix
    if (!_stricmp(extension, ".png"))
        type = S3_IMAGE_PNG;
    else if (!_stricmp(extension, ".exr"))
        type = S3_IMAGE_EXR;
    else if (!_stricmp(extension, ".hdr"))
        type = S3_IMAGE_HDR;
    else
        type = S3_IMAGE_ERROR;

    return type;
}

//s3Texture* s3LoadAsMipmap(std::vector<std::string> fileNames)
//{
//    s3Texture* texture = new s3Texture();
//
//    int32 width = 0, height = 0;
//    std::vector<float32*> data1;
//    std::vector<std::vector<unsigned char>> data2;
//    s3ImageType type;
//
//    std::vector<s3ImageDecoder> decoder(fileNames.size());
//    for (int32 i = 0; i <fileNames.size(); i++)
//    {
//        decoder[i].load(fileNames[i]);
//
//        if (i == 0)
//        {
//            width = decoder[i].getWidth();
//            height = decoder[i].getHeight();
//        }
//
//        type = decoder[i].getImageType();
//        switch (type)
//        {
//        case S3_IMAGE_PNG:
//            data2.push_back(decoder[i].getPNGData());
//            break;
//        case S3_IMAGE_EXR:
//            data1.push_back(decoder[i].getEXRData());
//            break;
//        case S3_IMAGE_HDR:
//            data1.push_back(decoder[i].getHDRData());
//            break;
//        case S3_IMAGE_ERROR:
//        default:
//            s3Log::warning("Error Image Type\n");
//            S3_SAFE_DELETE(texture);
//            return nullptr;
//        }
//    }
//
//    switch (type)
//    {
//    case S3_IMAGE_PNG:
//        texture->load(width, height, data2);
//        break;
//    case S3_IMAGE_EXR:
//    case S3_IMAGE_HDR:
//        texture->load(width, height, data1);
//        break;
//    case S3_IMAGE_ERROR:
//    default:
//        S3_SAFE_DELETE(texture);
//        return nullptr;
//    }
//    
//    return texture;
//}

//float s3SphericalTheta(const t3Vector3f &v)
//{
//    return t3Math::acosRad(t3Math::clamp(v.y, -1.f, 1.f));
//}
//
//float s3SphericalPhi(const t3Vector3f &v)
//{
//    float p = t3Math::atan2Rad(v.z, v.x);
//    return (p < 0.f) ? p + 2.f * T3MATH_PI : p;
//}

std::wstring s3S2WS(const std::string & str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string s3WS2S(const std::wstring & wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

// Copied from [OpenFrameworks](http://openframeworks.cc/)
std::string s3ToLower(const std::string & src)
{
    std::string dst = src;

    std::transform(dst.begin(), dst.end(), dst.begin(), ::tolower);

    return dst;
}

std::string s3ToUpper(const std::string & src)
{
    std::string dst = src;

    std::transform(dst.begin(), dst.end(), dst.begin(), ::toupper);

    return dst;
}

int s3ToInt(const std::string& intString)
{
    int x = 0;
    std::istringstream cur(intString);
    cur >> x;
    return x;
}

float s3ToFloat(const std::string& floatString)
{
    float x = 0;
    std::istringstream cur(floatString);
    cur >> x;
    return x;
}

double s3ToDouble(const std::string& doubleString)
{
    double x = 0;
    std::istringstream cur(doubleString);
    cur >> x;
    return x;
}

int64_t s3ToInt64(const std::string& intString)
{
    int64_t x = 0;
    std::istringstream cur(intString);
    cur >> x;
    return x;
}

bool s3ToBool(const std::string& boolString)
{
    auto lower = s3ToLower(boolString);
    if (lower == "true")
    {
        return true;
    }
    if (lower == "false")
    {
        return false;
    }
    bool x = false;
    std::istringstream cur(lower);
    cur >> x;
    return x;
}

char s3ToChar(const std::string& charString)
{
    char x = '\0';
    std::istringstream cur(charString);
    cur >> x;
    return x;
}

std::string s3ToHex(const char* value)
{
    // this function is necessary if you want to print a string
    // using a syntax like ofToHex("test")
    return s3ToHex((std::string) value);
}

// 十六进制字符串转换
int s3HexToInt(const std::string& intHexString)
{
    int x = 0;
    std::istringstream cur(intHexString);
    cur >> std::hex >> x;
    return x;
}

char s3HexToChar(const std::string& charHexString)
{
    int x = 0;
    std::istringstream cur(charHexString);
    cur >> std::hex >> x;
    return (char)x;
}

float s3HexToFloat(const std::string& floatHexString)
{
    union intFloatUnion
    {
        //int x;
        uint32_t i;
        float f;
    } myUnion;
    myUnion.i = 0;
    std::istringstream cur(floatHexString);
    cur >> std::hex >> myUnion.i;
    return myUnion.f;
}

std::string s3HexToString(const std::string& stringHexString)
{
    std::stringstream out;
    std::stringstream stream(stringHexString);
    // a hex string has two characters per byte
    std::size_t numBytes = stringHexString.size() / 2;
    for (std::size_t i = 0; i < numBytes; i++)
    {
        std::string curByte;
        // grab two characters from the hex string
        stream >> std::setw(2) >> curByte;
        // prepare to parse the two characters
        std::stringstream curByteStream(curByte);
        int cur = 0;
        // parse the two characters as a hex-encoded int
        curByteStream >> std::hex >> cur;
        // add the int as a char to our output stream
        out << (char)cur;
    }
    return out.str();
}
