#include <shader/s3Shader.h>
#include <core/log/s3Log.h>
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

s3Shader::s3Shader(const char* vertexPath, const char* fragmentPath)
{
    load(vertexPath, fragmentPath);
    compile();
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
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

bool s3Shader::IsLoaded() const
{
	return isLoaded;
}

int32 s3Shader::getProgram() const
{
	return program;
}

bool s3Shader::load(const char* vertexPath, const char* fragmentPath)
{
    // retrieve the vertex/fragment source code from filePath
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

    isLoaded = true;
    return isLoaded;
}

bool s3Shader::compile()
{
    if (!isLoaded) return false;

    const char* vShaderCode = vertexSource.c_str();
    const char* fShaderCode = fragmentSource.c_str();

    // compile shaders
    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    // print compile errors if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    };

    // similiar for Fragment Shader
    [...]

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    // print linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return true;
}
