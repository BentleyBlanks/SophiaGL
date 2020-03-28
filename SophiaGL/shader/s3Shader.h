#pragma once
#include <core/s3Settings.h>

class s3Shader
{
public:
    // constructor reads and builds the shader
    s3Shader(const char* vertexPath, const char* fragmentPath);
    ~s3Shader();

    // use/activate the shader
    void begin();
    void end();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;

    bool IsLoaded() const;
    int32 getProgram() const;

private:
    bool load(const char* vertexPath, const char* fragmentPath);
    bool compile();

    uint32 program = 0;
    bool isLoaded = false;

    // vs fs shader code
    std::string vertexSource;
    std::string fragmentSource;
};