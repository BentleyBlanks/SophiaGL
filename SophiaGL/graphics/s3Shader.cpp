#include <graphics/s3Shader.h>
#include <graphics/s3Texture.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


// --------------------------------------------------s3ShaderField--------------------------------------------------
void s3ShaderField::print() const
{
    s3Log::print("Type: %s, ", s3EnumUtil(s3ShaderFieldType).toString(type).c_str());

    switch (type)
    {
    case s3ShaderFieldType::none:
        break;
    case s3ShaderFieldType::texture:
        s3Log::print("Value: %d\n", texture);
        break;
    case s3ShaderFieldType::bool1:
        s3Log::print("Value: %d\n", bool1);
        break;
    case s3ShaderFieldType::int1:
        s3Log::print("Value: %d\n", int1);
        break;
    case s3ShaderFieldType::int2:
        s3Log::print("Value: [%d, %d]\n", int2.x, int2.y);
        break;
    case s3ShaderFieldType::int3:
        s3Log::print("Value: [%d, %d, %d]\n", int3.x, int3.y, int3.z);
        break;
    case s3ShaderFieldType::int4:
        s3Log::print("Value: [%d, %d, %d, %d]\n", int4.x, int4.y, int4.z, int4.w);
        break;
    case s3ShaderFieldType::float1:
        s3Log::print("Value: %f\n", float1);
        break;
    case s3ShaderFieldType::float2:
        s3Log::print("Value: [%f, %f]\n", float2.x, float2.y);
        break;
    case s3ShaderFieldType::float3:
        s3Log::print("Value: [%f, %f, %f]\n", float3.x, float3.y, float3.z);
        break;
    case s3ShaderFieldType::float4:
        s3Log::print("Value: [%f, %f, %f, %f]\n", float4.x, float4.y, float4.z, float4.w);
        break;
    case s3ShaderFieldType::mat4:
        s3Log::print("Value: [%f, %f, %f, %f][%f, %f, %f, %f][%f, %f, %f, %f][%f, %f, %f, %f]\n", 
                     mat4[0].x, mat4[0].y, mat4[0].z, mat4[0].w,
                     mat4[1].x, mat4[1].y, mat4[1].z, mat4[1].w, 
                     mat4[2].x, mat4[2].y, mat4[2].z, mat4[2].w, 
                     mat4[3].x, mat4[3].y, mat4[3].z, mat4[3].w);
        break;
    }
}

// --------------------------------------------------s3Shader--------------------------------------------------
s3Shader::s3Shader()
{}

s3Shader::s3Shader(const char* vertexPath, const char* fragmentPath)
{
    load(vertexPath, fragmentPath);
}

s3Shader::~s3Shader()
{}

void s3Shader::begin()
{
	glUseProgram(program);

    // bind all the cached field into pipeline
    for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    {
        const std::string& name = it->first;
        s3ShaderField& field    = it->second;
        switch (field.type)
        {
        case s3ShaderFieldType::none:
        {
            s3Log::warning("s3Shader field type: none\n");
            break;
        }
        case s3ShaderFieldType::texture:
        {
            s3Texture* tex = field.texture;
            int location = tex->getLocation();
            int textureID = tex->getTextureID();

            glActiveTexture(GL_TEXTURE0 + location);
            glBindTexture(GL_TEXTURE_2D, textureID);
            break;
        }
        case s3ShaderFieldType::bool1:
        {
            bool& bool1 = field.bool1;
            glUniform1i(glGetUniformLocation(program, name.c_str()), bool1);
            break;
        }
        case s3ShaderFieldType::int1:
        {
            int& int1 = field.int1;
            glUniform1i(glGetUniformLocation(program, name.c_str()), int1);
            break;
        }
        case s3ShaderFieldType::int2:
        {
            glm::ivec2& int2 = field.int2;
            glUniform2i(glGetUniformLocation(program, name.c_str()), int2.x, int2.y);
            break;
        }
        case s3ShaderFieldType::int3:
        {
            glm::ivec3& int3 = field.int3;
            glUniform3i(glGetUniformLocation(program, name.c_str()), int3.x, int3.y, int3.z);
            break;
        }
        case s3ShaderFieldType::int4:
        {
            glm::ivec4& int4 = field.int4;
            glUniform4i(glGetUniformLocation(program, name.c_str()), int4.x, int4.y, int4.z, int4.w);
            break;
        }
        case s3ShaderFieldType::float1:
        {
            float& float1 = field.float1;
            glUniform1f(glGetUniformLocation(program, name.c_str()), float1);
            break;
        }
        case s3ShaderFieldType::float2:
        {
            glm::vec2& float2 = field.float2;
            glUniform2f(glGetUniformLocation(program, name.c_str()), float2.x, float2.y);
            break;
        }
        case s3ShaderFieldType::float3:
        {
            glm::vec3& float3 = field.float3;
            glUniform3f(glGetUniformLocation(program, name.c_str()), float3.x, float3.y, float3.z);
            break;
        }
        case s3ShaderFieldType::float4:
        {
            glm::vec4& float4 = field.float4;
            glUniform4f(glGetUniformLocation(program, name.c_str()), float4.x, float4.y, float4.z, float4.w);
            break;
        }
        case s3ShaderFieldType::mat4:
        {
            glm::mat4& mat4 = field.mat4;
            glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, false, glm::value_ptr(mat4));
            break;
        }
        }
    }
}

void s3Shader::end()
{
	glUseProgram(0);

    // unbind all the cached field from pipeline
    for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    {
        const std::string& name = it->first;
        const s3ShaderField& field = it->second;

        switch (field.type)
        {
        case s3ShaderFieldType::none:
        {
            s3Log::warning("s3Shader field type: none\n");
            break;
        }
        case s3ShaderFieldType::texture:
        {
            glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0);
            break;
        }
        case s3ShaderFieldType::bool1:
            break;
        case s3ShaderFieldType::int1:
            break;
        case s3ShaderFieldType::int2:
            break;
        case s3ShaderFieldType::int3:
            break;
        case s3ShaderFieldType::int4:
            break;
        case s3ShaderFieldType::float1:
            break;
        case s3ShaderFieldType::float2:
            break;
        case s3ShaderFieldType::float3:
            break;
        case s3ShaderFieldType::float4:
            break;
        case s3ShaderFieldType::mat4:
            break;
        }
    }
}

float s3Shader::getFloat(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::float1)
        return 0.0f;

    return field.float1;
}

glm::vec2 s3Shader::getFloat2(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::float2)
        return glm::vec2();

    return field.float2;
}

glm::vec3 s3Shader::getFloat3(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::float3)
        return glm::vec3();

    return field.float3;
}

glm::vec4 s3Shader::getFloat4(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::float4)
        return glm::vec4();

    return field.float4;
}

int s3Shader::getInt(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::int1)
        return 0;

    return field.int1;
}

glm::ivec2 s3Shader::getInt2(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::int2)
        return glm::ivec2();

    return field.int2;
}

glm::ivec3 s3Shader::getInt3(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::int3)
        return glm::ivec3();

    return field.int3;
}

glm::ivec4 s3Shader::getInt4(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none || 
        field.type != s3ShaderFieldType::int4)
        return glm::ivec4();

    return field.int4;
}

glm::mat4 s3Shader::getMatrix(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::mat4)
        return glm::mat4();

    return field.mat4;
}

bool s3Shader::getBool(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::bool1)
        return false;

    return field.bool1;
}

s3Texture* s3Shader::getTexture(const std::string& name) const
{
    s3ShaderField field = getValue(name);

    if (field.type == s3ShaderFieldType::none ||
        field.type != s3ShaderFieldType::texture)
        return NULL;

    return field.texture;
}

bool s3Shader::setBool(const std::string& name, const bool& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::bool1;
    commonValue.bool1 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setInt(const std::string& name, const int& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::int1;
    commonValue.int1 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setInt2(const std::string& name, const glm::ivec2& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::int2;
    commonValue.int2 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setInt3(const std::string& name, const glm::ivec3& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::int3;
    commonValue.int3 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setInt4(const std::string& name, const glm::ivec4& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::int4;
    commonValue.int4 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setFloat(const std::string& name, const float& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::float1;
    commonValue.float1 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setFloat2(const std::string& name, const glm::vec2& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::float2;
    commonValue.float2 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setFloat3(const std::string& name, const glm::vec3& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::float3;
    commonValue.float3 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setFloat4(const std::string& name, const glm::vec4& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::float4;
    commonValue.float4 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setMatrix(const std::string& name, const glm::mat4& value)
{
    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::mat4;
    commonValue.mat4 = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setTexture(const std::string& name, s3Texture* value)
{
    if (!value) return false;

    glUniform1i(glGetUniformLocation(program, name.c_str()), value->getLocation());

    s3ShaderField commonValue;
    commonValue.type = s3ShaderFieldType::texture;
    commonValue.texture = value;
    setValue(name, commonValue);
    return true;
}

bool s3Shader::setValue(const std::string& name, s3ShaderField value)
{
    fieldMap[name] = value;
    return true;
}

s3ShaderField s3Shader::getValue(const std::string& name) const
{
    static s3ShaderField defaultField;

    auto it = fieldMap.find(name);
    if (it != fieldMap.end())
        return it->second;

    return defaultField;
}

void s3Shader::print() const
{
    //s3Log::debug("VS: %s, FS: %s\n", vertexSource.c_str(), fragmentSource.c_str());
    s3Log::debug("Program: %d\n", program);

    for (auto it = fieldMap.begin(); it != fieldMap.end(); it++)
    {
        const std::string& name    = it->first;
        const s3ShaderField& field = it->second;

        s3Log::debug("FieldName: %s, ", name.c_str());
        field.print();
    }
}

bool s3Shader::checkShader(unsigned int shader, bool isVertex)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		s3Log::error("%s shader compile failed, %s\n", isVertex ? "Vertex" : "Fragment", infoLog);
		return false;
	}

	return true;
}

bool s3Shader::checkProgram(unsigned int program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		s3Log::error("Program link failed, %s\n", infoLog);
		return false;
	}

	return true;
}

bool s3Shader::loadFromSource(const char* vShaderCode, const char* fShaderCode)
{
    //const char* vShaderCode = vertexSource.c_str();
    //const char* fShaderCode = fragmentSource.c_str();

    // vs Shader
    unsigned int vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vShaderCode, NULL);
    glCompileShader(vs);
    if (!checkShader(vs, true))
    {
        bIsLoaded = false;
        return false;
    }

    // fs shader
    unsigned int fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fShaderCode, NULL);
    glCompileShader(fs);
    if (!checkShader(fs, false))
    {
        bIsLoaded = false;
        return false;
    }

    // shader Program
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    if (!checkProgram(program))
    {
        bIsLoaded = false;
        return false;
    }

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vs);
    glDeleteShader(fs);

    bIsLoaded = true;
    return bIsLoaded;
}

bool s3Shader::load(const char* _vertexPath, const char* _fragmentPath)
{
    if (bIsLoaded)
    {
        glDeleteProgram(program);
        program = 0;

        vertexSource.clear();
        fragmentSource.clear();
        fieldMap.clear();

        bIsLoaded = false;
    }

    // retrieve the vs/fs source code from filePath
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(_vertexPath);
        fShaderFile.open(_fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        // close file handlers
        vShaderFile.close();
        fShaderFile.close();

        // convert stream into string
        vertexSource = vShaderStream.str();
        fragmentSource = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        s3Log::error("Error::shader file not succesfully read\n");
        bIsLoaded = false;
    }

    vertexPath   = _vertexPath;
    fragmentPath = _fragmentPath;

    return loadFromSource(vertexSource.c_str(), fragmentSource.c_str());

    //const char* vShaderCode = vertexSource.c_str();
    //const char* fShaderCode = fragmentSource.c_str();

    //// vs Shader
    //unsigned int vs;
    //vs = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vs, 1, &vShaderCode, NULL);
    //glCompileShader(vs);
    //if (!checkShader(vs, true))
    //{
    //    bIsLoaded = false;
    //    return false;
    //}

    //// fs shader
    //unsigned int fs;
    //fs = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fs, 1, &fShaderCode, NULL);
    //glCompileShader(fs);
    //if (!checkShader(fs, false))
    //{
    //    bIsLoaded = false;
    //    return false;
    //}

    //// shader Program
    //program = glCreateProgram();
    //glAttachShader(program, vs);
    //glAttachShader(program, fs);
    //glLinkProgram(program);
    //if (!checkProgram(program))
    //{
    //    bIsLoaded = false;
    //    return false;
    //}

    //// delete the shaders as they're linked into our program now and no longer necessery
    //glDeleteShader(vs);
    //glDeleteShader(fs);

    //bIsLoaded = true;
    //return bIsLoaded;
}

bool s3Shader::reload()
{
    if(!bIsLoaded) s3Log::warning("s3Shader::reload() need successfully called load() before\n");
    
    return load(vertexPath.c_str(), fragmentPath.c_str());
}
