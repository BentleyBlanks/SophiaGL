#include <graphics/s3Shader.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

s3Shader::s3Shader(const char* vertexPath, const char* fragmentPath)
{
    load(vertexPath, fragmentPath);
}

s3Shader::~s3Shader()
{}

void s3Shader::begin()
{
	glUseProgram(program);
}

void s3Shader::end()
{
	glUseProgram(0);
}

void s3Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void s3Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void s3Shader::setFloat(const std::string & name, float value) const
{
    uint32 location = glGetUniformLocation(program, name.c_str());
	glUniform1f(location, value);
}

bool s3Shader::IsLoaded() const
{
	return isLoaded;
}

int32 s3Shader::getProgram() const
{
	return program;
}

bool s3Shader::checkShader(uint32 shader)
{
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		s3Log::error("Error::shader compile failed, %s\n", infoLog);
		return false;
	}

	return true;
}

bool s3Shader::checkProgram(uint32 program)
{
	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		s3Log::error("Error::program link failed, %s\n", infoLog);
		return false;
	}

	return true;
}

bool s3Shader::load(const char* vertexPath, const char* fragmentPath)
{
    // retrieve the vs/fs source code from filePath
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
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
        s3Log::error("Error::shader file not succesfully read");
        isLoaded = false;
    }

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    // vs Shader
    uint32 vs;
    vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vShaderCode, NULL);
    glCompileShader(vs);
    if (!checkShader(vs))
    {
        isLoaded = false;
        return false;
    }

    // fs shader
    uint32 fs;
    fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fShaderCode, NULL);
    glCompileShader(fs);
    if (!checkShader(fs))
    {
        isLoaded = false;
        return false;
    }

    // shader Program
    program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    if (!checkProgram(program))
    {
        isLoaded = false;
        return false;
    }

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vs);
    glDeleteShader(fs);

    isLoaded = true;
    return isLoaded;
}