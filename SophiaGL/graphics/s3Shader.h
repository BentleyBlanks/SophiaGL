#pragma once
#include <core/s3Settings.h>
#include <glm/mat4x4.hpp>

class s3Shader
{
public:
    // constructor reads and builds the shader
    s3Shader();
    s3Shader(const char* vertexPath, const char* fragmentPath);
    ~s3Shader();

    // use/activate the shader
    void begin();
    void end();

    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setTexture(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setMatrix(const std::string& name, glm::mat4 mat) const;

    bool load(const char* vertexPath, const char* fragmentPath);
    bool isLoaded() const;

    unsigned int getProgram() const;

private:
    bool checkShader(unsigned int shader, bool isVertex);
    bool checkProgram(unsigned int program);

    unsigned int program = 0;
    bool bIsLoaded = false;

    // vs fs shader code
    std::string vertexSource;
    std::string fragmentSource;
};