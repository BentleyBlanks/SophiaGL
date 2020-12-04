#include <graphics/s3Shader.h>
#include <graphics/s3Texture.h>
#include <core/log/s3Log.h>
#include <core/util/s3UtilsString.h>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <shader_parser_gl.h>

// Just for simplify the code
#define S3_GET_VALUE(typeClassStr, typeNameStr) glm::typeClassStr value; \
                                       std::string typeName = typeNameStr; \
                                       getValue(typeName, name, (void*)(&value.x)); \
                                       return value

#define S3_GET_MAT_VALUE(typeClassStr, typeNameStr) glm::typeClassStr value; \
                                           std::string typeName = typeNameStr; \
                                           getValue(typeName, name, (void*)(&value[0].x)); \
                                           return value

#define S3_SET_VALUE(typeNameStr) std::string typeName = typeNameStr; \
                                  return setValue(typeName, name, (void*)(&value.x))

#define S3_SET_MAT_VALUE(typeNameStr) std::string typeName = typeNameStr; \
                                      return setValue(typeName, name, (void*)(&value[0].x))

// --------------------------------------------------s3ShaderField--------------------------------------------------
//void s3ShaderField::print() const
//{
//    s3Log::print("Type: %s, ", s3EnumUtil(s3ShaderFieldType).toString(type).c_str());
//
//    switch (type)
//    {
//    case s3ShaderFieldType::none:
//        break;
//    case s3ShaderFieldType::texture:
//        s3Log::print("Value: %d\n", texture);
//        break;
//    case s3ShaderFieldType::bool1:
//        s3Log::print("Value: %d\n", bool1);
//        break;
//    case s3ShaderFieldType::int1:
//        s3Log::print("Value: %d\n", int1);
//        break;
//    case s3ShaderFieldType::int2:
//        s3Log::print("Value: [%d, %d]\n", int2.x, int2.y);
//        break;
//    case s3ShaderFieldType::int3:
//        s3Log::print("Value: [%d, %d, %d]\n", int3.x, int3.y, int3.z);
//        break;
//    case s3ShaderFieldType::int4:
//        s3Log::print("Value: [%d, %d, %d, %d]\n", int4.x, int4.y, int4.z, int4.w);
//        break;
//    case s3ShaderFieldType::float1:
//        s3Log::print("Value: %f\n", float1);
//        break;
//    case s3ShaderFieldType::float2:
//        s3Log::print("Value: [%f, %f]\n", float2.x, float2.y);
//        break;
//    case s3ShaderFieldType::float3:
//        s3Log::print("Value: [%f, %f, %f]\n", float3.x, float3.y, float3.z);
//        break;
//    case s3ShaderFieldType::float4:
//        s3Log::print("Value: [%f, %f, %f, %f]\n", float4.x, float4.y, float4.z, float4.w);
//        break;
//    case s3ShaderFieldType::mat4:
//        s3Log::print("Value: [%f, %f, %f, %f][%f, %f, %f, %f][%f, %f, %f, %f][%f, %f, %f, %f]\n", 
//                     mat4[0].x, mat4[0].y, mat4[0].z, mat4[0].w,
//                     mat4[1].x, mat4[1].y, mat4[1].z, mat4[1].w, 
//                     mat4[2].x, mat4[2].y, mat4[2].z, mat4[2].w, 
//                     mat4[3].x, mat4[3].y, mat4[3].z, mat4[3].w);
//        break;
//    }
//}

// --------------------------------------------------s3Shader--------------------------------------------------
s3Shader::s3Shader()
{}

s3Shader::s3Shader(const char* filePath)
{
    load(filePath);
}

//s3Shader::s3Shader(const char* vertexPath, const char* fragmentPath)
//{
    //load(vertexPath, fragmentPath);
//}

s3Shader::~s3Shader()
{}

void s3Shader::begin()
{
	glUseProgram(program);

    // bind all the textures
    for (auto t : textureMap)
    {
        auto tex       = t.second;
        auto location  = tex->getLocation();
        auto textureID = tex->getTextureID();

        glActiveTexture(GL_TEXTURE0 + location);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }

    //// bind all the cached field into pipeline
    //for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    //{
    //    const std::string& name = it->first;
    //    s3ShaderField& field    = it->second;
    //    switch (field.type)
    //    {
    //    case s3ShaderFieldType::none:
    //    {
    //        s3Log::warning("s3Shader field type: none\n");
    //        break;
    //    }
    //    case s3ShaderFieldType::texture:
    //    {
    //        s3Texture* tex = field.texture;
    //        int location = tex->getLocation();
    //        int textureID = tex->getTextureID();

    //        glActiveTexture(GL_TEXTURE0 + location);
    //        glBindTexture(GL_TEXTURE_2D, textureID);
    //        break;
    //    }
    //    case s3ShaderFieldType::bool1:
    //    {
    //        bool& bool1 = field.bool1;
    //        glUniform1i(glGetUniformLocation(program, name.c_str()), bool1);
    //        break;
    //    }
    //    case s3ShaderFieldType::int1:
    //    {
    //        int& int1 = field.int1;
    //        glUniform1i(glGetUniformLocation(program, name.c_str()), int1);
    //        break;
    //    }
    //    case s3ShaderFieldType::int2:
    //    {
    //        glm::ivec2& int2 = field.int2;
    //        glUniform2i(glGetUniformLocation(program, name.c_str()), int2.x, int2.y);
    //        break;
    //    }
    //    case s3ShaderFieldType::int3:
    //    {
    //        glm::ivec3& int3 = field.int3;
    //        glUniform3i(glGetUniformLocation(program, name.c_str()), int3.x, int3.y, int3.z);
    //        break;
    //    }
    //    case s3ShaderFieldType::int4:
    //    {
    //        glm::ivec4& int4 = field.int4;
    //        glUniform4i(glGetUniformLocation(program, name.c_str()), int4.x, int4.y, int4.z, int4.w);
    //        break;
    //    }
    //    case s3ShaderFieldType::float1:
    //    {
    //        float& float1 = field.float1;
    //        glUniform1f(glGetUniformLocation(program, name.c_str()), float1);
    //        break;
    //    }
    //    case s3ShaderFieldType::float2:
    //    {
    //        glm::vec2& float2 = field.float2;
    //        glUniform2f(glGetUniformLocation(program, name.c_str()), float2.x, float2.y);
    //        break;
    //    }
    //    case s3ShaderFieldType::float3:
    //    {
    //        glm::vec3& float3 = field.float3;
    //        glUniform3f(glGetUniformLocation(program, name.c_str()), float3.x, float3.y, float3.z);
    //        break;
    //    }
    //    case s3ShaderFieldType::float4:
    //    {
    //        glm::vec4& float4 = field.float4;
    //        glUniform4f(glGetUniformLocation(program, name.c_str()), float4.x, float4.y, float4.z, float4.w);
    //        break;
    //    }
    //    case s3ShaderFieldType::mat4:
    //    {
    //        glm::mat4& mat4 = field.mat4;
    //        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, false, glm::value_ptr(mat4));
    //        break;
    //    }
    //    }
    //}
}

void s3Shader::end()
{
	glUseProgram(0);

    // unbind all textures
    for (auto tex : textureMap)
    {
        int location = tex.second->getLocation();

        glActiveTexture(GL_TEXTURE0 + location);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    //// unbind all the cached field from pipeline
    //for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    //{
    //    const std::string& name = it->first;
    //    const s3ShaderField& field = it->second;

    //    switch (field.type)
    //    {
    //    case s3ShaderFieldType::none:
    //    {
    //        s3Log::warning("s3Shader field type: none\n");
    //        break;
    //    }
    //    case s3ShaderFieldType::texture:
    //    {
    //        glBindTexture(GL_TEXTURE_2D, 0);
    //        glActiveTexture(GL_TEXTURE0);
    //        break;
    //    }
    //    case s3ShaderFieldType::bool1:
    //        break;
    //    case s3ShaderFieldType::int1:
    //        break;
    //    case s3ShaderFieldType::int2:
    //        break;
    //    case s3ShaderFieldType::int3:
    //        break;
    //    case s3ShaderFieldType::int4:
    //        break;
    //    case s3ShaderFieldType::float1:
    //        break;
    //    case s3ShaderFieldType::float2:
    //        break;
    //    case s3ShaderFieldType::float3:
    //        break;
    //    case s3ShaderFieldType::float4:
    //        break;
    //    case s3ShaderFieldType::mat4:
    //        break;
    //    }
    //}
}
glm::bvec1 s3Shader::getBool1(const std::string& name) const
{
    S3_GET_VALUE(bvec1, "bool");
}

glm::bvec2 s3Shader::getBool2(const std::string& name) const
{
    S3_GET_VALUE(bvec2, "bool2");
}

glm::bvec3 s3Shader::getBool3(const std::string& name) const
{
    S3_GET_VALUE(bvec3, "bool3");
}

glm::bvec4 s3Shader::getBool4(const std::string& name) const
{
    S3_GET_VALUE(bvec4, "bool4");
}

glm::ivec1 s3Shader::getInt1(const std::string& name) const
{
    S3_GET_VALUE(ivec1, "int");
}

glm::ivec2 s3Shader::getInt2(const std::string& name) const
{
    S3_GET_VALUE(ivec2, "int2");
}

glm::ivec3 s3Shader::getInt3(const std::string& name) const
{
    S3_GET_VALUE(ivec3, "int3");
}

glm::ivec4 s3Shader::getInt4(const std::string& name) const
{
    S3_GET_VALUE(ivec4, "int4");
}

glm::vec1 s3Shader::getFloat1(const std::string& name) const
{
    S3_GET_VALUE(vec1, "float");
}

glm::vec2 s3Shader::getFloat2(const std::string& name) const
{
    S3_GET_VALUE(vec2, "float2");
}

glm::vec3 s3Shader::getFloat3(const std::string& name) const
{
    S3_GET_VALUE(vec3, "float3");
}

glm::vec4 s3Shader::getFloat4(const std::string& name) const
{
    S3_GET_VALUE(vec4, "float4");
}

glm::dvec1 s3Shader::getDouble1(const std::string& name) const
{
    S3_GET_VALUE(dvec1, "double");
}

glm::dvec2 s3Shader::getDouble2(const std::string& name) const
{
    S3_GET_VALUE(dvec2, "double2");
}

glm::dvec3 s3Shader::getDouble3(const std::string& name) const
{
    S3_GET_VALUE(dvec3, "double3");
}

glm::dvec4 s3Shader::getDouble4(const std::string& name) const
{
    S3_GET_VALUE(dvec4, "double4");
}

glm::mat3 s3Shader::getMatrix3(const std::string& name) const
{
    S3_GET_MAT_VALUE(mat3, "float3x3");
}

glm::mat4 s3Shader::getMatrix4(const std::string& name) const
{
    S3_GET_MAT_VALUE(mat4, "float4x4");
}

s3Texture* s3Shader::getTexture(const std::string& name) const
{
    auto iter = textureMap.find(name);
    if (iter == textureMap.end()) 
        return nullptr;

    return iter->second;
}

bool s3Shader::setBool1(const std::string& name, const glm::bvec1& value)
{
    S3_SET_VALUE("bool");
}

bool s3Shader::setBool2(const std::string& name, const glm::bvec2& value)
{
    S3_SET_VALUE("bool2");
}

bool s3Shader::setBool3(const std::string& name, const glm::bvec3& value)
{
    S3_SET_VALUE("bool3");
}

bool s3Shader::setBool4(const std::string& name, const glm::bvec4& value)
{
    S3_SET_VALUE("bool4");
}

bool s3Shader::setInt1(const std::string& name, const glm::ivec1& value)
{
    S3_SET_VALUE("int");
}

bool s3Shader::setInt2(const std::string& name, const glm::ivec2& value)
{
    S3_SET_VALUE("int2");
}

bool s3Shader::setInt3(const std::string& name, const glm::ivec3& value)
{
    S3_SET_VALUE("int3");
}

bool s3Shader::setInt4(const std::string& name, const glm::ivec4& value)
{
    S3_SET_VALUE("int4");
}

bool s3Shader::setFloat1(const std::string& name, const glm::vec1& value)
{
    S3_SET_VALUE("float");
}

bool s3Shader::setFloat2(const std::string& name, const glm::vec2& value)
{
    S3_SET_VALUE("float2");
}

bool s3Shader::setFloat3(const std::string& name, const glm::vec3& value)
{
    S3_SET_VALUE("float3");
}

bool s3Shader::setFloat4(const std::string& name, const glm::vec4& value)
{
    S3_SET_VALUE("float4");
}

bool s3Shader::setDouble1(const std::string& name, const glm::dvec1& value)
{
    S3_SET_VALUE("double");
}

bool s3Shader::setDouble2(const std::string& name, const glm::dvec2& value)
{
    S3_SET_VALUE("double2");
}

bool s3Shader::setDouble3(const std::string& name, const glm::dvec3& value)
{
    S3_SET_VALUE("double3");
}

bool s3Shader::setDouble4(const std::string& name, const glm::dvec4& value)
{
    S3_SET_VALUE("double4");
}

//bool s3Shader::setMatrix3(const std::string& name, const glm::mat3& value)
//{
//    S3_SET_MAT_VALUE("float3x3");
//}

bool s3Shader::setMatrix4(const std::string& name, const glm::mat4& value)
{
    S3_SET_MAT_VALUE("float4x4");
}

bool s3Shader::setTexture(const std::string& name, s3Texture* value)
{
    if (!value) return false;

    // Ref: https://learnopengl.com/Getting-started/Textures
    // only need to set once
    // (uniform localtion, texture location)
    glUniform1i(glGetUniformLocation(program, name.c_str()), value->getLocation());
    
    textureMap[name] = value;

    return true;
}

//bool s3Shader::setValue(const std::string& name, s3ShaderField value)
//{
//    if (!findValueInUniformElemList(name)) return false;
//
//    fieldMap[name] = value;
//    return true;
//}
//
//s3ShaderField s3Shader::getValue(const std::string& name) const
//{
//    static s3ShaderField defaultField;
//
//    auto it = fieldMap.find(name);
//    if (it != fieldMap.end())
//        return it->second;
//
//    return defaultField;
//}

void s3Shader::print() const
{
    //s3Log::debug("VS: %s, FS: %s\n", vertexSource.c_str(), fragmentSource.c_str());
    s3Log::debug("Program: %d\n", program);

    //for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    //{
    //    const std::string& name    = it->first;
    //    const s3ShaderField& field = it->second;

    //    s3Log::debug("FieldName: %s, ", name.c_str());
    //    field.print();
    //}
}

bool s3Shader::load(const char* _shaderFilePath)
{
    if (bIsLoaded)
    {
        // reload
        //for (auto it = programMap.begin(); it != programMap.end(); it++)
        //{
        //    glDeleteProgram(it->second);
        //    it->second = 0;
        //}
        //programMap.clear();
        glDeleteProgram(program);

        vertexSource.clear();
        fragmentSource.clear();
        //fieldMap.clear();

        bIsLoaded = false;
    }

    // retrieve the vs / fs source code from lua
	const char* shaderName = shader_load_gl(_shaderFilePath);
	if (!shaderName) return false;

    filePath = _shaderFilePath;
    name     = shaderName;

    if (g_shadermap_gl.find(shaderName) == g_shadermap_gl.end()) return false;
	auto& shader = g_shadermap_gl[shaderName];
    
    auto& subshader_list = shader.subshader_list;
    if (subshader_list.size() <= 0) return false;

    auto& pass_list = subshader_list[0].pass_list;
    if (pass_list.size() <= 0) return false;

    // now only supported 1 pass
    program = pass_list[0].program;

    updateInputLayout(pass_list[0].input_layout_list);
    updateUniformData(pass_list[0].uniform_buffer_elem_list);

    s3Log::success("Shader:%s build succeed\n", filePath.c_str());

    bIsLoaded = true;
	return true;
}

bool s3Shader::setValue(const std::string& typeName, const std::string& attrName, const void* dataPtr)
{
    if (!bIsLoaded || !dataPtr) return false;

    auto elem = findValueInUniformElemList(typeName, attrName);
    if (!elem) return false;

    // CPU Mem for getter / setter
    memcpy((char*)uniformData + elem->type_offset, dataPtr, elem->type_size);

    // copy to GPU Mem
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferSubData(GL_UNIFORM_BUFFER, elem->type_offset, elem->type_size, uniformData);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    return false;
}

void s3Shader::getValue(const std::string& typeName, const std::string& attrName, void* dataPtr) const
{
    if (!bIsLoaded || !dataPtr) return;

    auto elem = findValueInUniformElemList(typeName, attrName);
    if (!elem) return;

    memcpy(dataPtr, (char*)uniformData + elem->type_offset, elem->type_size);
}

//int s3Shader::getTypeSize(const std::string& typeName) const
//{
//    // Sync with Lua
//    static std::map<std::string, int> typeList =
//    {
//		{"float"   , 4},
//		{"float2"  , 8},
//		{"float3"  , 16},
//		{"float4"  , 16},
//		{"bool"    , 4},
//		{"bool2"   , 8},
//		{"bool3"   , 16},
//		{"bool4"   , 16},
//		{"int"     , 4},
//		{"int2"    , 8},
//		{"int3"    , 16},
//		{"int4"    , 16},
//		{"double"  , 8},
//		{"double2" , 16},
//		{"double3" , 32},
//		{"double4" , 32},
//		{"float3x3", 48},
//		{"float4x4", 64}
//    };
//
//    auto iter = typeList.find(typeName);
//    if (iter == typeList.end()) return 0;
//
//    return iter->second;
//}

const shader_uniform_buffer_elem_gl* s3Shader::findValueInUniformElemList(const std::string& typeName, const std::string& attrName) const
{
    if (!bIsLoaded) return nullptr;

    auto& shader          = g_shadermap_gl[name];
    auto& subshaderList   = shader.subshader_list;
    auto& passList        = subshaderList[0].pass_list;
    auto& uniformElemList = passList[0].uniform_buffer_elem_list;

    for (auto& elem : uniformElemList)
    {
        if (elem.attr_name == attrName && elem.type_name == typeName)
            return &elem;
    }

    s3Log::warning("Not found attribute: %s %s in uniform block\n", typeName.c_str(), attrName.c_str());
    return nullptr;
}

void s3Shader::updateInputLayout(const std::vector<shader_input_layout_elem_gl>& inputLayoutList)
{
    // initialize a new, shader related, input layout
    auto* newInputLayout = new s3InputLayout();
    for (auto iter = inputLayoutList.begin(); iter < inputLayoutList.end(); iter++)
    {
        auto channel = iter->channel;
        if (channel == eC_NONE || channel >= eC_COUNT)
            continue;

        newInputLayout->channels[channel]   = true;
        newInputLayout->dataTypes[channel]  = iter->data_type;
        newInputLayout->dimensions[channel] = iter->dimension;
    }

    auto& manager = s3InputLayoutManager::getInstance();
    bool needToAdd = true;
    if (inputLayoutHandle > 0)
    {
        // check if handle is valid
        auto oldInputLayout = manager.get(inputLayoutHandle);
        if (!oldInputLayout.isEqual(s3InputLayout::invalid))
        {
            if (oldInputLayout.isEqual(*newInputLayout))
            {
                // no need to add repeatedly
                S3_SAFE_DELETE(newInputLayout);
                needToAdd = false;
            }
            else
            {
                // remove and add new input layout
                manager.remove(inputLayoutHandle);
            }
        }
    }
    if (needToAdd) inputLayoutHandle = manager.add(*newInputLayout);
}

void s3Shader::updateUniformData(const std::vector<shader_uniform_buffer_elem_gl>& uniformElemList)
{
    if (uniformElemList.size() <= 0) return;

    S3_SAFE_DELETE(uniformData);

    // last node store uniform buffer's special info
    // calculate attributes offset by std140 layout
    auto lastAttr = uniformElemList[uniformElemList.size() - 1];
    unsigned int length = lastAttr.type_offset;

    // initialize uniform buffer data
    uniformData = malloc(length);
    memset(uniformData, 0, length);

    // ShaderConductor's default uniform block's name = 'type_cb_' + fileName + '_' + index
    std::string ubName("type_cb_");
    ubName += s3GetFileName(filePath);
    ubName += "_1";

    // supporse there is only 1 binding point
    GLuint uniformBlockIndex = glGetUniformBlockIndex(program, ubName.c_str());
    if (uniformBlockIndex == GL_INVALID_INDEX)
    {
        s3Log::error("Could not get index of uniform block %s check if such uniform block really exists!\n", ubName.c_str());
        return;
    }
    glUniformBlockBinding(program, uniformBlockIndex, 0);

    // uniform buffer object
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, length, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // only 0 binding point is working
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, length);
}

bool s3Shader::reload()
{
    if(!bIsLoaded) s3Log::warning("s3Shader::reload() need successfully called load() before\n");
    
    //return load(vertexPath.c_str(), fragmentPath.c_str());
    return load(filePath.c_str());
}
