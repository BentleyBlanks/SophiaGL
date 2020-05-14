#include <graphics/s3Material.h>
#include <graphics/s3Shader.h>

s3Material::s3Material(s3Shader& shader) : shader(&shader)
{
}

float s3Material::getFloat(const std::string& name) const
{
	if(!shader) return 0.0f;
	return shader->getFloat(name);
}

glm::vec2 s3Material::getFloat2(const std::string& name) const
{
	if (!shader) return glm::vec2();
	return shader->getFloat2(name);
}

glm::vec3 s3Material::getFloat3(const std::string& name) const
{
	if (!shader) return glm::vec3();
	return shader->getFloat3(name);
}

glm::vec4 s3Material::getFloat4(const std::string& name) const
{
	if (!shader) return glm::vec4();
	return shader->getFloat4(name);
}

int s3Material::getInt(const std::string& name) const
{
	if (!shader) return 0;
	return shader->getInt(name);
}

glm::ivec2 s3Material::getInt2(const std::string& name) const
{
	if (!shader) return glm::ivec2();
	return shader->getInt2(name);
}

glm::ivec3 s3Material::getInt3(const std::string& name) const
{
	if (!shader) return glm::ivec3();
	return shader->getInt3(name);
}

glm::ivec4 s3Material::getInt4(const std::string& name) const
{
	if (!shader) return glm::ivec4();
	return shader->getInt4(name);
}

glm::mat4 s3Material::getMatrix(const std::string& name) const
{
	if (!shader) return glm::mat4();
	return shader->getMatrix(name);
}

bool s3Material::getBool(const std::string& name) const
{
	if (!shader) return false;
	return shader->getBool(name);
}

s3Texture* s3Material::getTexture(const std::string& name) const
{
	if (!shader) return nullptr;
	return shader->getTexture(name);
}

bool s3Material::setBool(const std::string& name, const bool& value)
{
	if (!shader) return false;
	return shader->setBool(name, value);
}

bool s3Material::setInt(const std::string& name, const int& value)
{
	if (!shader) return false;
	return shader->setInt(name, value);
}

bool s3Material::setInt2(const std::string& name, const glm::ivec2& value)
{
	if (!shader) return false;
	return shader->setInt2(name, value);
}

bool s3Material::setInt3(const std::string& name, const glm::ivec3& value)
{
	if (!shader) return false;
	return shader->setInt3(name, value);
}

bool s3Material::setInt4(const std::string& name, const glm::ivec4& value)
{
	if (!shader) return false;
	return shader->setInt4(name, value);
}

bool s3Material::setFloat(const std::string& name, const float& value)
{
	if (!shader) return false;
	return shader->setFloat(name, value);
}

bool s3Material::setFloat2(const std::string& name, const glm::vec2& value)
{
	if (!shader) return false;
	return shader->setFloat2(name, value);
}

bool s3Material::setFloat3(const std::string& name, const glm::vec3& value)
{
	if (!shader) return false;
	return shader->setFloat3(name, value);
}

bool s3Material::setFloat4(const std::string& name, const glm::vec4& value)
{
	if (!shader) return false;
	return shader->setFloat4(name, value);
}

bool s3Material::setMatrix(const std::string& name, const glm::mat4& value)
{
	if (!shader) return false;
	return shader->setMatrix(name, value);
}

bool s3Material::setTexture(const std::string& name, s3Texture* value)
{
	if (!shader) return false;
	return shader->setTexture(name, value);
}
