#include <3d/s3Mesh.h>
#include <glad/glad.h>

//--! ref: https://docs.unity3d.com/2017.4/Documentation/ScriptReference/Mesh.html
s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	indices.clear();
	//positions.clear();
	//normals.clear();
	//tangents.clear();
	//uvs.clear();
}

//void s3Mesh::setTriangles(const std::vector<unsigned int>& subIndices, int submesh)
//{
//	if (submesh < 0 || submesh >= indexRangeList.size())
//	{
//		s3Log::warning("s3Mesh::setTriangles() invalid submesh index: %d\n", submesh);
//		return;
//	}
//
//	int newCount = (int)subIndices.size();
//	auto& range = indexRangeList[submesh];
//
//	// std::copy won't alloc mem when exceeded, ensure enough space mannually
//	std::vector<unsigned int> temp;
//	auto tempSize = indices.size() - range.start - range.count;
//	if (tempSize > 0)
//	{
//		temp.resize(tempSize);
//
//		// copy rest of the triangle list
//		auto restIndicesStart = indices.begin() + range.start + range.count;
//		std::copy(restIndicesStart, indices.end(), temp.begin());
//	}
//
//	// diffCount could be < 0, smaller than before is acceptable
//	auto diffCount = newCount - range.count;
//	indices.resize(indices.size() + diffCount);
//
//	auto subIndicesStart = indices.begin() + range.start;
//	std::copy(subIndices.begin(), subIndices.end(), subIndicesStart);
//
//	// update range list
//	range.count = newCount;
//	updateRangeList();
//
//	if (temp.size() > 0)
//	{
//		auto copyBackStart = indices.begin() + range.start + newCount;
//		std::copy(temp.begin(), temp.end(), copyBackStart);
//	}
//}
//
//void s3Mesh::setSubMeshCount(int subMeshCount)
//{
//	int currentCount = (int)indexRangeList.size();
//	indexRangeList.resize(subMeshCount);
//	updateRangeList();
//}
//
//void s3Mesh::updateRangeList()
//{
//	if (indexRangeList.size() <= 0) return;
//
//	auto lastRange = indexRangeList[0];
//	for (int i = 1; i < indexRangeList.size(); i++)
//	{
//		auto& range = indexRangeList[i];
//		range.start = lastRange.start + lastRange.count;
//
//		lastRange = range;
//	}
//}

//const std::vector<unsigned int>& s3Mesh::getTriangles(int submesh) const
//{
//	static std::vector<unsigned int> temp;
//
//	if (submesh < 0 || submesh >= indexRangeList.size())
//	{
//		s3Log::warning("s3Mesh::getTriangles() invalid submesh index: %d\n", submesh);
//		return temp;
//	}
//
//	auto& range = indexRangeList[submesh];
//	temp.resize(range.count);
//
//	std::copy(indices.begin() + range.start, indices.begin() + range.start + range.count, temp.begin());
//	return temp;
//}

// input layout  = vao
// vertex buffer = vbo
// index buffer  = ebo
void s3Mesh::apply()
{
	int pCount = (int)positions.size();
	int nCount = (int)normals.size();
	int tCount = (int)uvs.size();
	if (pCount < 0 || 
	   (nCount > 0 && pCount != nCount) || 
	   (tCount > 0 && pCount != tCount) ||
	   (tCount > 0 && nCount > 0 && !(pCount == nCount == tCount)))
	{
		s3Log::warning("s3Mesh's properties error, position: %d, normals: %d, uvs: %d\n", pCount, nCount, tCount);
		return;
	}

	// pCount must be greater than 0, but for code unify, check it everytime
	//unsigned long long pSize = sizeof(glm::vec3) * pCount;
	//unsigned long long nSize = sizeof(glm::vec3) * nCount;
	//unsigned long long tSize = sizeof(glm::vec2) * tCount;

	vertices.clear();
	for (int i = 0; i < pCount; i++)
	{
		if (pCount > 0)
		{
			auto& position = positions[i];
			vertices.push_back(position.x);
			vertices.push_back(position.y);
			vertices.push_back(position.z);
		}

		if (nCount > 0)
		{
			auto& normal = normals[i];
			vertices.push_back(normal.x);
			vertices.push_back(normal.y);
			vertices.push_back(normal.z);
		}

		if (tCount > 0)
		{
			auto& uv = uvs[i];
			vertices.push_back(uv.x);
			vertices.push_back(uv.y);
		}
	}

	// vao generation and bind
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// vbo, vertex buffer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	// ebo, index buffer
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	// input layout
	int index = 0;
	unsigned long long offset = 0;
	if (pCount > 0)
	{
		int size = sizeof(float) * 3;
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, size, (void*)offset);
		index  += 1;
		offset += size;
	}

	if (nCount > 0)
	{
		int size = sizeof(float) * 3;
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, size, (void*)offset);
		index  += 1;
		offset += size;
	}

	if (tCount > 0)
	{
		int size = sizeof(float) * 2;
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, size, (void*)offset);
		index  += 1;
		offset += size;
	}

	// not supported tangents now

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
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

