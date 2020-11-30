#include <graphics/s3Material.h>
#include <graphics/s3Shader.h>

s3Material::s3Material(s3Shader& shader) : shader(&shader)
{
}

glm::bvec1 s3Material::getBool1(const std::string& name) const
{
	return shader->getBool1(name);
}

glm::bvec2 s3Material::getBool2(const std::string& name) const
{
	return shader->getBool2(name);
}

glm::bvec3 s3Material::getBool3(const std::string& name) const
{
	return shader->getBool3(name);
}

glm::bvec4 s3Material::getBool4(const std::string& name) const
{
	return shader->getBool4(name);
}

glm::ivec1 s3Material::getInt1(const std::string& name) const
{
	return shader->getInt1(name);
}

glm::ivec2 s3Material::getInt2(const std::string& name) const
{
	return shader->getInt2(name);
}

glm::ivec3 s3Material::getInt3(const std::string& name) const
{
	return shader->getInt3(name);
}

glm::ivec4 s3Material::getInt4(const std::string& name) const
{
	return shader->getInt4(name);
}

glm::vec1 s3Material::getFloat1(const std::string& name) const
{
	return shader->getFloat1(name);
}

glm::vec2 s3Material::getFloat2(const std::string& name) const
{
	return shader->getFloat2(name);
}

glm::vec3 s3Material::getFloat3(const std::string& name) const
{
	return shader->getFloat3(name);
}

glm::vec4 s3Material::getFloat4(const std::string& name) const
{
	return shader->getFloat4(name);
}

glm::dvec1 s3Material::getDouble1(const std::string& name) const
{
	return shader->getDouble1(name);
}

glm::dvec2 s3Material::getDouble2(const std::string& name) const
{
	return shader->getDouble2(name);
}

glm::dvec3 s3Material::getDouble3(const std::string& name) const
{
	return shader->getDouble3(name);
}

glm::dvec4 s3Material::getDouble4(const std::string& name) const
{
	return shader->getDouble4(name);
}

//glm::mat3 s3Material::getMatrix3(const std::string& name) const
//{
//	return shader->getMatrix3(name);
//}

glm::mat4 s3Material::getMatrix4(const std::string& name) const
{
	return shader->getMatrix4(name);
}

s3Texture* s3Material::getTexture(const std::string& name) const
{
	return shader->getTexture(name);
}

bool s3Material::setBool1(const std::string& name, const glm::bvec1& value)
{
	return shader->setBool1(name, value);
}

bool s3Material::setBool2(const std::string& name, const glm::bvec2& value)
{
	return shader->setBool2(name, value);
}

bool s3Material::setBool3(const std::string& name, const glm::bvec3& value)
{
	return shader->setBool3(name, value);
}

bool s3Material::setBool4(const std::string& name, const glm::bvec4& value)
{
	return shader->setBool4(name, value);
}

bool s3Material::setInt1(const std::string& name, const glm::ivec1& value)
{
	return shader->setInt1(name, value);
}

bool s3Material::setInt2(const std::string& name, const glm::ivec2& value)
{
	return shader->setInt2(name, value);
}

bool s3Material::setInt3(const std::string& name, const glm::ivec3& value)
{
	return shader->setInt3(name, value);
}

bool s3Material::setInt4(const std::string& name, const glm::ivec4& value)
{
	return shader->setInt4(name, value);
}

bool s3Material::setFloat1(const std::string& name, const glm::vec1& value)
{
	return shader->setFloat1(name, value);
}

bool s3Material::setFloat2(const std::string& name, const glm::vec2& value)
{
	return shader->setFloat2(name, value);
}

bool s3Material::setFloat3(const std::string& name, const glm::vec3& value)
{
	return shader->setFloat3(name, value);
}

bool s3Material::setFloat4(const std::string& name, const glm::vec4& value)
{
	return shader->setFloat4(name, value);
}

bool s3Material::setDouble1(const std::string& name, const glm::dvec1& value)
{
	return shader->setDouble1(name, value);
}

bool s3Material::setDouble2(const std::string& name, const glm::dvec2& value)
{
	return shader->setDouble2(name, value);
}

bool s3Material::setDouble3(const std::string& name, const glm::dvec3& value)
{
	return shader->setDouble3(name, value);
}

bool s3Material::setDouble4(const std::string& name, const glm::dvec4& value)
{
	return shader->setDouble4(name, value);
}

//bool s3Material::setMatrix3(const std::string& name, const glm::mat3& value)
//{
//	return shader->setMatrix3(name, value);
//}

bool s3Material::setMatrix4(const std::string& name, const glm::mat4& value)
{
	return shader->setMatrix4(name, value);
}

bool s3Material::setTexture(const std::string& name, s3Texture* value)
{
	return shader->setTexture(name, value);
}