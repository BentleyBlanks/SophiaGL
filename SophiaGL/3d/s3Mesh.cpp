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
	if (submesh < 0 || submesh >= triangleRangeList.size())
	{
		s3Log::warning("s3Mesh::setTriangles() invalid submesh index: %d\n", submesh);
		return;
	}

	int newCount = (int)subIndices.size();
	auto& range = triangleRangeList[submesh];

	// std::copy won't alloc mem when exceeded, ensure enough space mannually
	std::vector<int> temp;
	auto tempSize = triangles.size() - range.start - range.count;
	if (tempSize > 0)
	{
		temp.resize(tempSize);

		// copy rest of the triangle list
		auto restIndicesStart = triangles.begin() + range.start + range.count;
		std::copy(restIndicesStart, triangles.end(), temp.begin());
	}

	// diffCount could be < 0, smaller than before is acceptable
	auto diffCount = newCount - range.count;
	triangles.resize(triangles.size() + diffCount);

	auto subIndicesStart = triangles.begin() + range.start;
	std::copy(subIndices.begin(), subIndices.end(), subIndicesStart);

	// update range list
	range.count = newCount;
	updateRangeList();

	if (temp.size() > 0)
	{
		auto copyBackStart = triangles.begin() + range.start + newCount;
		std::copy(temp.begin(), temp.end(), copyBackStart);
	}
}

void s3Mesh::setSubMeshCount(int subMeshCount)
{
	int currentCount = (int)triangleRangeList.size();
	triangleRangeList.resize(subMeshCount);
	updateRangeList();
}

void s3Mesh::updateRangeList()
{
	if (triangleRangeList.size() <= 0) return;

	auto lastRange = triangleRangeList[0];
	for (int i = 1; i < triangleRangeList.size(); i++)
	{
		auto& range = triangleRangeList[i];
		range.start = lastRange.start + lastRange.count;

		lastRange = range;
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
