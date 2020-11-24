#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>
#include <3d/s3VertexData.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class s3Texture;

//s3Enum(s3ShaderFieldType,
//       none,
//       float1,
//       float2,
//       float3,
//       float4,
//       bool1,
//       bool2,
//       bool3,
//       bool4,
//       int1,
//       int2,
//       int3,
//       int4,
//       double1,
//       double2,
//       double3,
//       double4,
//       float3x3,
//       float3x4,
//       float4x3,
//       float4x4);

//class s3ShaderField
//{
//public:
//    void print() const;
//
//    union
//    {
//        s3Texture* texture;
//
//        bool bool1;
//        float float1;
//        int int1;
//
//        glm::ivec2 int2;
//        glm::ivec3 int3;
//        glm::ivec4 int4;
//
//        glm::vec2 float2;
//        glm::vec3 float3;
//        glm::vec4 float4;
//
//        glm::mat4 mat4;
//    };
//
//    s3ShaderFieldType type = s3ShaderFieldType::int1;
//};

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
    glm::bvec1 getBool1(const std::string& name) const;
    glm::bvec2 getBool2(const std::string& name) const;
    glm::bvec3 getBool3(const std::string& name) const;
    glm::bvec4 getBool4(const std::string& name) const;
    glm::ivec1 getInt1(const std::string& name) const;
    glm::ivec2 getInt2(const std::string& name) const;
    glm::ivec3 getInt3(const std::string& name) const;
    glm::ivec4 getInt4(const std::string& name) const;
    glm::vec1 getFloat1(const std::string& name) const;
    glm::vec2 getFloat2(const std::string& name) const;
    glm::vec3 getFloat3(const std::string& name) const;
    glm::vec4 getFloat4(const std::string& name) const;
    glm::dvec1 getDouble(const std::string& name) const;
    glm::dvec2 getDouble2(const std::string& name) const;
    glm::dvec3 getDouble3(const std::string& name) const;
    glm::dvec4 getDouble4(const std::string& name) const;
    glm::mat3 getMatrix3(const std::string& name) const;
    glm::mat4 getMatrix4(const std::string& name) const;
    s3Texture* getTexture(const std::string& name) const;
    //bool getKeyword(std::string name) const;

    //bool setKeyword(std::string name, bool enableKeyword);
    bool setBool1(const std::string& name, const glm::bvec1& value);
    bool setBool2(const std::string& name, const glm::bvec2& value);
    bool setBool3(const std::string& name, const glm::bvec3& value);
    bool setBool4(const std::string& name, const glm::bvec4& value);
    bool setInt1(const std::string& name, const glm::ivec1& value);
    bool setInt2(const std::string& name, const glm::ivec2& value);
    bool setInt3(const std::string& name, const glm::ivec3& value);
    bool setInt4(const std::string& name, const glm::ivec4& value);
    bool setFloat1(const std::string& name, const glm::vec1& value);
    bool setFloat2(const std::string& name, const glm::vec2& value);
    bool setFloat3(const std::string& name, const glm::vec3& value);
    bool setFloat4(const std::string& name, const glm::vec4& value);
    bool setDouble1(const std::string& name, const glm::vec1& value);
    bool setDouble2(const std::string& name, const glm::vec2& value);
    bool setDouble3(const std::string& name, const glm::vec3& value);
    bool setDouble4(const std::string& name, const glm::vec4& value);
    bool setMatrix3(const std::string& name, const glm::mat3& value);
    bool setMatrix4(const std::string& name, const glm::mat4& value);
    bool setTexture(const std::string& name, s3Texture* value);

    // common setter / getter
    //bool setValue(const std::string& name, s3ShaderField value);
    //s3ShaderField getValue(const std::string& name) const;

    // input layout getter
    unsigned int getInputLayoutHandle() const { return inputLayoutHandle; }

private:
    bool setValue(const std::string& typeName, const std::string& attrName, const void* dataPtr, unsigned int dataSize);
    void getValue(const std::string& typeName, const std::string& attrName, void* dataPtr, unsigned int dataSize) const;

    int getTypeSize(const std::string& typeName) const;

    int findValueInUniformElemList(const std::string& attrName) const;
    void updateInputLayout(const std::vector<shader_input_layout_elem_gl>& inputLayoutList);
    void updateUniformData(const std::vector<shader_uniform_buffer_elem_gl>& uniformElemList);

    //std::map<std::string, unsigned int> programMap;
    unsigned int program = 0;
    int inputLayoutHandle = -1;

    bool bIsLoaded = false;

    // vs fs shader code
    std::string vertexSource, fragmentSource;
    std::string shaderFilePath;
    std::string name;
    //std::string vertexPath, fragmentPath;

    //std::map<std::string, s3ShaderField> fieldMap;
    std::map<std::string, s3Texture*> textureMap;
    void* uniformData = nullptr;
};