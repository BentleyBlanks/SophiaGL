#pragma once
#include <core/s3Settings.h>
#include <core/s3Enum.h>
#include <glm/glm.hpp>

class s3Mesh
{
public:
	s3Mesh();
	~s3Mesh();

	//	Clears all vertex data and all triangle indices.
	void clear();

	// new a mesh object
	void setVertices(const std::vector<glm::vec3>& _vertices) { vertices.assign(_vertices.begin(), _vertices.end()); }
	void setNormals(const std::vector<glm::vec3>& _normals) { normals.assign(_normals.begin(), _normals.end()); }
	void setTangents(const std::vector<glm::vec3>& _tangents) { tangents.assign(_tangents.begin(), _tangents.end()); }
	void setUV(const std::vector<glm::vec2>& _uv) { uv.assign(_uv.begin(), _uv.end()); }

	// Sets the index buffer for the sub-Mesh.
	void setTriangles(const std::vector<int>& _indices, int submesh);
	void setSubMeshCount(int subMeshCount);

	void setPosition(const glm::vec3& _position) { position = _position; }
	void setRotation(const glm::mat4& _rotation) { rotation = _rotation; }

	const std::vector<glm::vec3>& getVertices() const { return vertices; }
	const std::vector<glm::vec3>& getNormals() const { return normals; }
	const std::vector<glm::vec3>& getTangents() const { return tangents; }
	const std::vector<glm::vec2>& getUV() const { return uv; }

	// Gets the index buffer for the specified sub mesh on this instance.
	const std::vector<int>& getTriangles(int submesh) const { return triangles; }
	int getSubmeshCount() const { return (int)triangleRangeList.size(); }

	const glm::vec3& getPosition() const { return position; }
	const glm::mat4& getRotation() const { return rotation; }
	
	// could be moved changed into GameObject.CreatePrimitive
	static s3Mesh& createCube();
	static s3Mesh& createPlane();
	static s3Mesh& createSphere();
	static s3Mesh& createCapsule();
	static s3Mesh& createCylinder();

//private:
	void updateRangeList();

	struct s3MeshTriangleRange
	{
		int start = 0;
		int count = 0;
	};

	// submesh indices
	std::vector<int> triangles;
	std::vector<s3MeshTriangleRange> triangleRangeList;

	// vertex's pnt buffer
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec3> tangents;
	std::vector<glm::vec2> uv;

	// opengl render data
	unsigned int vao = 0, vbo = 0, ebo = 0;

	// transform data
	glm::vec3 position = glm::vec3();
	glm::mat4 rotation = glm::mat4();
};