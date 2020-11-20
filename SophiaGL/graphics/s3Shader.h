#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>
#include <3d/s3VertexData.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class s3Texture;

s3Enum(s3ShaderFieldType,
       none,
       texture,
       bool1,
       int1,
       int2,
       int3,
       int4,
       float1,
       float2,
       float3,
       float4,
       mat4);

class s3ShaderField
{
public:
    void print() const;

    union
    {
        s3Texture* texture;

        bool bool1;
        float float1;
        int int1;

        glm::ivec2 int2;
        glm::ivec3 int3;
        glm::ivec4 int4;

        glm::vec2 float2;
        glm::vec3 float3;
        glm::vec4 float4;

        glm::mat4 mat4;
    };

    s3ShaderFieldType type = s3ShaderFieldType::int1;
};

class s3Shader
{
public:
    // constructor reads and builds the shader
    s3Shader();
    s3Shader(const char* shaderFilePath);
    //s3Shader(const char* vertexPath, const char* fragmentPath);
    ~s3Shader();

    //bool load(const char* vertexPath, const char* fragmentPath);
    bool load(const char* shaderFilePath);
    bool isLoaded() const { return bIsLoaded; }
    bool reload();

    //const std::map<std::string, unsigned int>& getPrograms() const { return programMap; }
    unsigned int getProgram() const { return program; }
    const std::string& getName() const { return name; }
    const std::string& getVertexSource() const { return vertexSource; }
    const std::string& getFragmentSource() const { return fragmentSource; }

    // debug
    void print() const;

//private:
    // use/activate the shader
    void begin();
    void end();

    // utility uniform functions
    float getFloat(const std::string& name) const;
    glm::vec2 getFloat2(const std::string& name) const;
    glm::vec3 getFloat3(const std::string& name) const;
    glm::vec4 getFloat4(const std::string& name) const;
    int getInt(const std::string& name) const;
    glm::ivec2 getInt2(const std::string& name) const;
    glm::ivec3 getInt3(const std::string& name) const;
    glm::ivec4 getInt4(const std::string& name) const;
    glm::mat4 getMatrix(const std::string& name) const;
    bool getBool(const std::string& name) const;
    s3Texture* getTexture(const std::string& name) const;
    //bool getKeyword(std::string name) const;

    //bool setKeyword(std::string name, bool enableKeyword);
    bool setBool(const std::string& name, const bool& value);
    bool setInt(const std::string& name, const int& value);
    bool setInt2(const std::string& name, const glm::ivec2& value);
    bool setInt3(const std::string& name, const glm::ivec3& value);
    bool setInt4(const std::string& name, const glm::ivec4& value);
    bool setFloat(const std::string& name, const float &value);
    bool setFloat2(const std::string& name, const glm::vec2& value);
    bool setFloat3(const std::string& name, const glm::vec3& value);
    bool setFloat4(const std::string& name, const glm::vec4& value);
    bool setMatrix(const std::string& name, const glm::mat4& value);
    bool setTexture(const std::string& name, s3Texture* value);

    // common setter / getter
    bool setValue(const std::string& name, s3ShaderField value);
    s3ShaderField getValue(const std::string& name) const;

    // input layout getter
    unsigned int getInputLayoutHandle() const { return inputLayoutHandle; }

private:
    void updateInputLayout(const std::vector<shader_input_layout_elem_gl>& inputLayoutList);

    //std::map<std::string, unsigned int> programMap;
    unsigned int program = 0;
    int inputLayoutHandle = -1;

    bool bIsLoaded = false;

    // vs fs shader code
    std::string vertexSource, fragmentSource;
    std::string shaderFilePath;
    std::string name;
    //std::string vertexPath, fragmentPath;

    std::map<std::string, s3ShaderField> fieldMap;
};