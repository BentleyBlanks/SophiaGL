#pragma once
#include <core/s3Settings.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <graphics/s3Shader.h>

class s3Texture;
class s3Material
{
public:
	s3Material(s3Shader& shader);
    ~s3Material() {}

	const s3Shader& getShader() const { return *shader; }

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
    bool setFloat(const std::string& name, const float& value);
    bool setFloat2(const std::string& name, const glm::vec2& value);
    bool setFloat3(const std::string& name, const glm::vec3& value);
    bool setFloat4(const std::string& name, const glm::vec4& value);
    bool setMatrix(const std::string& name, const glm::mat4& value);
    bool setTexture(const std::string& name, s3Texture* value);

    void print() { shader->print(); } 

private:
	s3Shader* shader = nullptr;

    bool bIsLoaded = false;
};