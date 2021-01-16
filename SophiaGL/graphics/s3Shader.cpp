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


// --------------------------------------------------Just for simplify the code--------------------------------------------------
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

// --------------------------------------------------s3Shader--------------------------------------------------
s3Shader::s3Shader()
{}

s3Shader::s3Shader(const char* filePath)
{
    load(filePath);
}

s3Shader::~s3Shader()
{}

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

//glm::mat3 s3Shader::getMatrix3(const std::string& name) const
//{
//    S3_GET_MAT_VALUE(mat3, "float3x3");
//}

glm::mat4 s3Shader::getMatrix4(const std::string& name) const
{
    S3_GET_MAT_VALUE(mat4, "float4x4");
}

s3Texture* s3Shader::getTexture(const std::string& name) const
{
    auto iter = textureMap.find(name);
    if (iter == textureMap.end()) 
        return nullptr;

    return iter->second.texture;
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
    glUniform1i(glGetUniformLocation(program, name.c_str()), textureMap[name].location);
    
    textureMap[name].texture = value;

    return true;
}

void s3Shader::print() const
{
    // --------------------------------------------------print function helper--------------------------------------------------
#define S3_UNIFORMDATA_PRINT_1(dataTypeName, formatStr) glm::dataTypeName##1 dataTypeName##1; \
                                                        memcpy(&dataTypeName##1.x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                        s3Log::print("[%s %s] : [%"##formatStr"]\n", \
                                                                     elem.type_name.c_str(), \
                                                                     elem.attr_name.c_str(), \
                                                                     dataTypeName##1)

#define S3_UNIFORMDATA_PRINT_2(dataTypeName, formatStr) glm::dataTypeName##2 dataTypeName##2; \
                                                        memcpy(&dataTypeName##2.x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                        s3Log::print("[%s %s] : [%"##formatStr", %"##formatStr"]\n", \
                                                                     elem.type_name.c_str(), \
                                                                     elem.attr_name.c_str(), \
                                                                     dataTypeName##2.x, \
                                                                     dataTypeName##2.y)

#define S3_UNIFORMDATA_PRINT_3(dataTypeName, formatStr) glm::dataTypeName##3 dataTypeName##3; \
                                                        memcpy(&dataTypeName##3.x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                        s3Log::print("[%s %s] : [%"##formatStr", %"##formatStr", %"##formatStr"]\n", \
                                                                     elem.type_name.c_str(), \
                                                                     elem.attr_name.c_str(), \
                                                                     dataTypeName##3.x, \
                                                                     dataTypeName##3.y, \
                                                                     dataTypeName##3.z)

#define S3_UNIFORMDATA_PRINT_4(dataTypeName, formatStr) glm::dataTypeName##4 dataTypeName##4; \
                                                        memcpy(&dataTypeName##4.x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                        s3Log::print("[%s %s] : [%"##formatStr", %"##formatStr", %"##formatStr", %"##formatStr"]\n", \
                                                                     elem.type_name.c_str(), \
                                                                     elem.attr_name.c_str(), \
                                                                     dataTypeName##4.x, \
                                                                     dataTypeName##4.y, \
                                                                     dataTypeName##4.z, \
                                                                     dataTypeName##4.w)

#define S3_UNIFORMDATA_PRINT_9(dataTypeName, formatStr) glm::mat3 mat3; \
                                                        memcpy(&mat3[0].x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                        s3Log::print("[%s %s] : \n[%"##formatStr", %"##formatStr", %"##formatStr"]\n[%"##formatStr", %"##formatStr", %"##formatStr"]\n[%"##formatStr", %"##formatStr", %"##formatStr"]\n\n", \
                                                                      elem.type_name.c_str(), \
                                                                      elem.attr_name.c_str(), \
                                                                      mat3[0].x, mat3[0].y, mat3[0].z, \
                                                                      mat3[1].x, mat3[1].y, mat3[1].z, \
                                                                      mat3[2].x, mat3[2].y, mat3[2].z)

#define S3_UNIFORMDATA_PRINT_16(dataTypeName, formatStr) glm::mat4 mat4; \
                                                         memcpy(&mat4[0].x, (char*)uniformData + elem.type_offset, elem.type_size); \
                                                         s3Log::print("[%s %s] : \n[%"##formatStr", %"##formatStr", %"##formatStr", %"##formatStr"]\n[%"##formatStr", %"##formatStr", %"##formatStr", %"##formatStr"]\n[%"##formatStr", %"##formatStr", %"##formatStr", %"##formatStr"]\n[%"##formatStr", %"##formatStr", %"##formatStr", %"##formatStr"]\n\n", \
                                                                      elem.type_name.c_str(), \
                                                                      elem.attr_name.c_str(), \
                                                                      mat4[0].x, mat4[0].y, mat4[0].z, mat4[0].w, \
                                                                      mat4[1].x, mat4[1].y, mat4[1].z, mat4[1].w, \
                                                                      mat4[2].x, mat4[2].y, mat4[2].z, mat4[2].w, \
                                                                      mat4[3].x, mat4[3].y, mat4[3].z, mat4[3].w)

#define S3_UNIFORMDATA_PRINT(dataTypeName, formatStr) switch (elem.type_count)                                \
                                                      {                                                       \
                                                      case 1:                                                 \
                                                          S3_UNIFORMDATA_PRINT_1(dataTypeName, formatStr);    \
                                                          break;                                              \
                                                      case 2:                                                 \
                                                          S3_UNIFORMDATA_PRINT_2(dataTypeName, formatStr);    \
                                                          break;                                              \
                                                      case 3:                                                 \
                                                          S3_UNIFORMDATA_PRINT_3(dataTypeName, formatStr);    \
                                                          break;                                              \
                                                      case 4:                                                 \
                                                          S3_UNIFORMDATA_PRINT_4(dataTypeName, formatStr);    \
                                                          break;                                              \
                                                      }

#define S3_UNIFORMDATA_MAT_PRINT(dataTypeName, formatStr) switch (elem.type_count)                                \
                                                          {                                                       \
                                                          case 9:                                                 \
                                                              S3_UNIFORMDATA_PRINT_9(dataTypeName, formatStr);    \
                                                              break;                                              \
                                                          case 16:                                                \
                                                              S3_UNIFORMDATA_PRINT_16(dataTypeName, formatStr);   \
                                                              break;                                              \
                                                          }

    if (!bIsLoaded) return;

    s3Log::debug("\nVS: %s\n", vertexSource.c_str(), fragmentSource.c_str());
    s3Log::debug("\nFS: %s\n", vertexSource.c_str(), fragmentSource.c_str());
    s3Log::debug("\n[Arrtibutes]\n");

    auto& shader = g_shadermap_gl[name];
    auto& subshaderList = shader.subshader_list;
    auto& passList = subshaderList[0].pass_list;
    auto& uniformElemList = passList[0].uniform_buffer_elem_list;

    // Data field
    //static char* valuePtr = (char*)malloc(16 * sizeof(float));
    for (auto& elem : uniformElemList)
    {
        // last node stored special info of uniform buffer
        if (elem.type_count == 0) continue;

        if (elem.type_name == "int")
        {
            S3_UNIFORMDATA_PRINT(ivec, "d")
        }
        else if (elem.type_name == "double")
        {
            S3_UNIFORMDATA_PRINT(dvec, "f")
        }
        else if (elem.type_name == "float")
        {
            S3_UNIFORMDATA_PRINT(vec, "f")
        }
        else if (elem.type_name == "bool")
        {
            S3_UNIFORMDATA_PRINT(bvec, "d")
        }
        else if (elem.type_name == "float3x3")
        {
            S3_UNIFORMDATA_MAT_PRINT(mat3, "f")
        }
        else if (elem.type_name == "float4x4")
        {
            S3_UNIFORMDATA_MAT_PRINT(mat4, "f")
        }
    }

    // Texture binding
    for (auto it = textureMap.begin(); it != textureMap.end(); it++)
    {
        auto texObj   = it->second;
        auto tex      = texObj.texture;
        auto location = texObj.location;
        s3Log::print("[Texture]: Name: %s, Width: %d, Height: %d, ID: %d\n, Location: %d",
                     it->first.c_str(), 
                     tex->getWidth(), 
                     tex->getHeight(),
                     tex->getTextureID(),
                     location);
    }
}

void s3Shader::begin()
{
    glUseProgram(program);

    // Cull
    switch(cull)
    {
    case eCULL_FRONT:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        break;
    case eCULL_OFF:
        glDisable(GL_CULL_FACE);
        break;
    case eCULL_BACK:
    default:
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        break;
    }

    // ZTest
    glEnable(GL_DEPTH_TEST);
    switch (ztest)
    {
    case eZTEST_LESS:
        glDepthFunc(GL_LESS);
        break;
    case eZTEST_GREATER:
        glDepthFunc(GL_GREATER);
        break;
    case eZTEST_GEQUAL:
        glDepthFunc(GL_GEQUAL);
        break;
    case eZTEST_EQUAL:
        glDepthFunc(GL_EQUAL);
        break;
    case eZTEST_NOTEQUAL:
        glDepthFunc(GL_NOTEQUAL);
        break;
    case eZTEST_ALWAYS:
        glDepthFunc(GL_ALWAYS);
        break;
    case eZTEST_LEQUAL:
    default:
        glDepthFunc(GL_LEQUAL);
        break;
    }

    // ZWrite
    switch (zwrite)
    {
    case eWRITE_OFF:
        glDepthMask(GL_FALSE);
        break;
    case eWRITE_ON:
    default:
        glDepthMask(GL_TRUE);
        break;
    }
    
    // bind all the textures
    for (auto t : textureMap)
    {
        auto tex       = t.second;
        auto location  = tex.location;
        auto textureID = tex.texture->getTextureID();

        glActiveTexture(GL_TEXTURE0 + location);
        glBindTexture(GL_TEXTURE_2D, textureID);
    }
}

void s3Shader::end()
{
    glUseProgram(0);

    // unbind all textures
    for (auto tex : textureMap)
    {
        int location = tex.second.location;

        glActiveTexture(GL_TEXTURE0 + location);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
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
    auto& pass     = pass_list[0];
    program        = pass.program;
    cull           = pass.cull;
    ztest          = pass.ztest;
    zwrite         = pass.zwrite;
    vertexSource   = pass.vs_source;
    fragmentSource = pass.fs_source;

    updateInputLayout(pass_list[0].input_layout_list);
    updateUniformData(pass_list[0].uniform_buffer_elem_list);
    updateTextureMap(pass_list[0].texture_list);

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
    glBufferSubData(GL_UNIFORM_BUFFER, elem->type_offset, elem->type_size, dataPtr);
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

    // uniform buffer object, glBufferData will allocate and store the data
    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    glBufferData(GL_UNIFORM_BUFFER, length, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    // only 0 binding point is working
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, length);
}

void s3Shader::updateTextureMap(const std::vector<shader_texture_gl>& textureList)
{
    for (auto tex : textureList)
    {
        s3TextureGLInfo texInfo;
        texInfo.location = tex.location;
        texInfo.texture  = nullptr;

        textureMap[tex.name] = texInfo;
    }
}

bool s3Shader::reload()
{
    if(!bIsLoaded) s3Log::warning("s3Shader::reload() need successfully called load() before\n");
    
    //return load(vertexPath.c_str(), fragmentPath.c_str());
    return load(filePath.c_str());
}
