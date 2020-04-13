#include <graphics/s3Shader.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

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

void s3Shader::setTexture(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}

void s3Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void s3Shader::setMatrix(const std::string& name, glm::mat4 mat) const
{
    unsigned int location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

bool s3Shader::isLoaded() const
{
	return bIsLoaded;
}

unsigned int s3Shader::getProgram() const
{
	return program;
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
        s3Log::error("Error::shader file not succesfully read\n");
        bIsLoaded = false;
    }

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

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