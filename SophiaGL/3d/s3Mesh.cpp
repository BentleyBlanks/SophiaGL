#include "s3Mesh.h"

//--! ref: https://docs.unity3d.com/2017.4/Documentation/ScriptReference/Mesh.html
s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	triangles.clear();
	vertices.clear();
	normals.clear();
	tangents.clear();
	uv.clear();
}

void s3Mesh::setTriangles(const std::vector<int>& subIndices, int submesh)
{
	if (submesh < 0 && submesh >= triangleRangeList.size()) return;

	auto range = triangleRangeList[submesh];

	// cound only copy part of the triangle list
	std::vector<int> temp;
	auto restIndicesStart = triangles.begin() + range.start + subIndices.size();
	std::copy(restIndicesStart, triangles.end(), temp);
	
	auto subIndicesStart = triangles.begin() + range.start;
	std::copy(subIndices.begin(), subIndices.end(), subIndicesStart);

	if (temp.size() <= 0) return;
	std::copy(temp.begin(), temp.end(), restIndicesStart);
}

void s3Mesh::setSubMeshCount(int subMeshCount)
{
	int currentCount = triangleRangeList.size();
	triangleRangeList.resize(subMeshCount);

	// filling the new submesh range
	auto lastRange = triangleRangeList[currentCount - 1];
	for (int i = currentCount; i < subMeshCount; i++)
	{
		triangleRangeList[i].start = lastRange.start + lastRange.count;
		triangleRangeList[i].count = 0;
	}
}

s3Mesh& s3Mesh::createCube()
{
	auto mesh = new s3Mesh();

	return *mesh;
}

s3Mesh& s3Mesh::createPlane()
{
	auto mesh = new s3Mesh();

	return *mesh;
}

s3Mesh& s3Mesh::createSphere()
{
	auto mesh = new s3Mesh();

	return *mesh;
}

s3Mesh& s3Mesh::createCapsule()
{
	auto mesh = new s3Mesh();

	return *mesh;
}

s3Mesh& s3Mesh::createCylinder()
{
	auto mesh = new s3Mesh();

	return *mesh;
}
