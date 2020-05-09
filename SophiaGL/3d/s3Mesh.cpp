#include "s3Mesh.h"

s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	indices.clear();
	vertices.clear();
	normals.clear();
	tangents.clear();
	uv.clear();
}

bool s3Mesh::setIndices(const std::vector<int> & _indices)
{
	indices.assign(_indices.begin(), _indices.end());
	return true;
}

bool s3Mesh::setVertices(const std::vector<glm::vec3>& _vertices)
{
	vertices.assign(_vertices.begin(), _vertices.end());
	return true;
}

bool s3Mesh::setNormals(const std::vector<glm::vec3>& _normals)
{
	normals.assign(_normals.begin(), _normals.end());
	return true;
}

bool s3Mesh::setTangents(const std::vector<glm::vec3>& _tangents)
{
	tangents.assign(_tangents.begin(), _tangents.end());
	return true;
}

bool s3Mesh::setUV(const std::vector<glm::vec2>& _uv)
{
	uv.assign(_uv.begin(), _uv.end());
	return true;
}

bool s3Mesh::setPosition(const glm::vec3& _position)
{
	position = _position;
	return true;
}

bool s3Mesh::setRotation(const glm::mat4& _rotation)
{
	rotation = _rotation;
	return true;
}

const std::vector<int>& s3Mesh::getIndices() const
{
	return indices;
}

const std::vector<glm::vec3>& s3Mesh::getVertices() const
{
	return vertices;
}

const std::vector<glm::vec3>& s3Mesh::getNormals() const
{
	return normals;
}

const std::vector<glm::vec3>& s3Mesh::getTangents() const
{
	return tangents;
}

const std::vector<glm::vec2>& s3Mesh::getUV() const
{
	return uv;
}

const glm::vec3& s3Mesh::getPosition() const
{
	return position;
}

const glm::mat4& s3Mesh::getRotation() const
{
	return rotation;
}
