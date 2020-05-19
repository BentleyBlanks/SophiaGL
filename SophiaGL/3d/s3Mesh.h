#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>
#include <glm/glm.hpp>

class s3Renderer;
class s3Mesh
{
public:
	s3Mesh();
	~s3Mesh();

	//	Clears all vertex data and all triangle indices.
	void clear();

	// new a mesh object
	void setVertices(const std::vector<glm::vec3>& _vertices) { positions.assign(_vertices.begin(), _vertices.end()); }
	void setNormals(const std::vector<glm::vec3>& _normals) { normals.assign(_normals.begin(), _normals.end()); }
	void setTangents(const std::vector<glm::vec3>& _tangents) { tangents.assign(_tangents.begin(), _tangents.end()); }
	void setUVs(const std::vector<glm::vec2>& _uvs) { uvs.assign(_uvs.begin(), _uvs.end()); }

	// Sets the index buffer for the sub-Mesh.
	void setTriangles(const std::vector<unsigned int>& _indices, int submesh);
	void setSubMeshCount(int subMeshCount);

	void setPosition(const glm::vec3& _position) { positionWS = _position; }
	void setRotation(const glm::mat4& _rotation) { rotationWS = _rotation; }

	const std::vector<glm::vec3>& getVertices() const { return positions; }
	const std::vector<glm::vec3>& getNormals() const { return normals; }
	const std::vector<glm::vec3>& getTangents() const { return tangents; }
	const std::vector<glm::vec2>& getUVs() const { return uvs; }

	// Gets the index buffer for the specified sub mesh on this instance.
	const std::vector<unsigned int>& getTriangles(int submesh) const;
	int getSubmeshCount() const { return (int)triangleRangeList.size(); }

	const glm::vec3& getPosition() const { return positionWS; }
	const glm::mat4& getRotation() const { return rotationWS; }
	
	// could be moved changed into GameObject.CreatePrimitive
	static s3Mesh& createCube();
	static s3Mesh& createPlane();
	static s3Mesh& createSphere();
	static s3Mesh& createCapsule();
	static s3Mesh& createCylinder();

	// called mannually after changing any of the mesh's property
	// Unity Mesh no need to called apply() after changing properties
	void apply();

	friend class s3Renderer;

//private:
	void updateRangeList();

	struct s3MeshTriangleRange
	{
		unsigned int start = 0;
		unsigned int count = 0;
	};

	// submesh indices
	std::vector<unsigned int> triangles;
	std::vector<s3MeshTriangleRange> triangleRangeList;

	// vertex's buffer
	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> uvs;

	// vertex data
	//std::vector<float> vertices;

	// opengl render data
	unsigned int vao = 0, vbo = 0, ebo = 0;

	// transform data
	glm::vec3 positionWS = glm::vec3();
	glm::mat4 rotationWS = glm::mat4();
};