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

	// std::copy won't alloc mem when exceeded, ensure enough space here
	auto& range = triangleRangeList[submesh];
	auto diffCount = subIndices.size() - range.count;
	if (triangles.capacity() < triangles.size() + diffCount)
		triangles.resize(triangles.size() + diffCount);

	// ensure enough space here
	std::vector<int> temp;
	auto tempSize = triangles.size() - range.start - subIndices.size();
	if(tempSize > 0) temp.resize(tempSize);
	
	// copy rest of the triangle list
	auto restIndicesStart = triangles.begin() + range.start + subIndices.size();
	std::copy(restIndicesStart, triangles.end(), temp.begin());
	
	auto subIndicesStart = triangles.begin() + range.start;
	std::copy(subIndices.begin(), subIndices.end(), subIndicesStart);

	// update range list
	range.count = (int)subIndices.size();
	updateRangeList();

	if (temp.size() <= 0) return;
	std::copy(temp.begin(), temp.end(), restIndicesStart);
}

void s3Mesh::setSubMeshCount(int subMeshCount)
{
	int currentCount = (int)triangleRangeList.size();
	triangleRangeList.resize(subMeshCount);
	updateRangeList();

	//// initialize range list
	//if (currentCount <= 0)
	//{
	//	updateRangeList();
	//	return;
	//}

	//// filling the new submesh range
	//auto lastRange = triangleRangeList[currentCount - 1];
	//for (int i = currentCount; i < subMeshCount; i++)
	//{
	//	triangleRangeList[i].start = lastRange.start + lastRange.count;
	//	triangleRangeList[i].count = 0;
	//}
}

void s3Mesh::updateRangeList()
{
	if (triangleRangeList.size() <= 0) return;

	auto lastRange = triangleRangeList[0];
	for (int i = 1; i < triangleRangeList.size(); i++)
	{
		auto& range = triangleRangeList[i];
		range.start = lastRange.start + lastRange.count;
		//range.count = 0;

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
