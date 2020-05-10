#pragma once
#include <core/s3Settings.h>
#include <glm/glm.hpp>

class s3Mesh
{
public:
	s3Mesh();
	~s3Mesh();

	//	Clears all vertex data and all triangle indices.
	void clear();

	// new a mesh object
	void setIndices(const std::vector<int>& _indices) { indices.assign(_indices.begin(), _indices.end()); }
	void setVertices(const std::vector<glm::vec3>& _vertices) { vertices.assign(_vertices.begin(), _vertices.end()); }
	void setNormals(const std::vector<glm::vec3>& _normals) { normals.assign(_normals.begin(), _normals.end()); }
	void setTangents(const std::vector<glm::vec3>& _tangents) { tangents.assign(_tangents.begin(), _tangents.end()); }
	void setUV(const std::vector<glm::vec2>& _uv) { uv.assign(_uv.begin(), _uv.end()); }

	void setPosition(const glm::vec3& _position) { position = _position; }
	void setRotation(const glm::mat4& _rotation) { rotation = _rotation; }

	const std::vector<int>& getIndices() const { return indices; }
	const std::vector<glm::vec3>& getVertices() const { return vertices; }
	const std::vector<glm::vec3>& getNormals() const { return normals; }
	const std::vector<glm::vec3>& getTangents() const { return tangents; }
	const std::vector<glm::vec2>& getUV() const { return uv; }
	
	const glm::vec3& getPosition() const { return position; }
	const glm::mat4& getRotation() const { return rotation; }
	
private:
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> uv;

	// opengl render data
	unsigned int vao, vbo, ebo;

	// transform data
	glm::vec3 position;
	glm::mat4 rotation;
};