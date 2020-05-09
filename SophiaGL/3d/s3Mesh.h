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

	bool setIndices(const std::vector<int>& indices);
	bool setVertices(const std::vector<glm::vec3>& vertices);
	bool setNormals(const std::vector<glm::vec3>& normals);
	bool setTangents(const std::vector<glm::vec3>& tangents);
	bool setUV(const std::vector<glm::vec2>& uv);

	bool setPosition(const glm::vec3& position);
	bool setRotation(const glm::mat4& rotation);

	const std::vector<int>& getIndices() const;
	const std::vector<glm::vec3>& getVertices() const;
	const std::vector<glm::vec3>& getNormals() const;
	const std::vector<glm::vec3>& getTangents() const;
	const std::vector<glm::vec2>& getUV() const;
	
	const glm::vec3& getPosition() const;
	const glm::mat4& getRotation() const;

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