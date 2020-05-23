#include <core/util/s3UtilsString.h>

#include <iostream>  
#include <sstream>
#include <iomanip>
#include <iterator>
#include <codecvt>

std::wstring s3S2WS(const std::string& str)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string s3WS2S(const std::wstring& wstr)
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

// Copied from [OpenFrameworks](http://openframeworks.cc/)
std::string s3ToLower(const std::string& src)
{
    std::string dst = src;

    std::transform(dst.begin(), dst.end(), dst.begin(), ::tolower);

    return dst;
}

std::string s3ToUpper(const std::string& src)
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
