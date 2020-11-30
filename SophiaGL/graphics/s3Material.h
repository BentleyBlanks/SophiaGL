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
    glm::dvec1 getDouble1(const std::string& name) const;
    glm::dvec2 getDouble2(const std::string& name) const;
    glm::dvec3 getDouble3(const std::string& name) const;
    glm::dvec4 getDouble4(const std::string& name) const;
    //glm::mat3 getMatrix3(const std::string& name) const;
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
    bool setDouble1(const std::string& name, const glm::dvec1& value);
    bool setDouble2(const std::string& name, const glm::dvec2& value);
    bool setDouble3(const std::string& name, const glm::dvec3& value);
    bool setDouble4(const std::string& name, const glm::dvec4& value);
    //bool setMatrix3(const std::string& name, const glm::mat3& value);
    bool setMatrix4(const std::string& name, const glm::mat4& value);
    bool setTexture(const std::string& name, s3Texture* value);

    void print() { shader->print(); } 

private:
	s3Shader* shader = nullptr;

    bool bIsLoaded = false;
};