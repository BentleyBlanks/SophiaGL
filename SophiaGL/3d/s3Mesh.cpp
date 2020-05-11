#include <3d/s3Mesh.h>
#include <glad/glad.h>

//--! ref: https://docs.unity3d.com/2017.4/Documentation/ScriptReference/Mesh.html
s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	triangles.clear();
	positions.clear();
	normals.clear();
	tangents.clear();
	uvs.clear();
}

void s3Mesh::setTriangles(const std::vector<unsigned int>& subIndices, int submesh)
{
	if (submesh < 0 || submesh >= triangleRangeList.size())
	{
		s3Log::warning("s3Mesh::setTriangles() invalid submesh index: %d\n", submesh);
		return;
	}

	int newCount = (int)subIndices.size();
	auto& range = triangleRangeList[submesh];

	// std::copy won't alloc mem when exceeded, ensure enough space mannually
	std::vector<unsigned int> temp;
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

const std::vector<unsigned int>& s3Mesh::getTriangles(int submesh) const
{
	static std::vector<unsigned int> temp;

	if (submesh < 0 || submesh >= triangleRangeList.size())
	{
		s3Log::warning("s3Mesh::getTriangles() invalid submesh index: %d\n", submesh);
		return temp;
	}

	auto& range = triangleRangeList[submesh];
	temp.resize(range.count);

	std::copy(triangles.begin() + range.start, triangles.begin() + range.start + range.count, temp.begin());
	return temp;
}

// input layout  = vao
// vertex buffer = vbo
// index buffer  = ebo
void s3Mesh::apply()
{
	int pSize = (int)positions.size();
	int nSize = (int)normals.size();
	int tSize = (int)uvs.size();
	if (pSize <= 0 || (nSize >= 0 && pSize != nSize) || (tSize >= 0 && pSize != tSize))
	{
		s3Log::warning("s3Mesh's properties error, position: %d, normals: %d, uvs: %d\n", pSize, nSize, tSize);
		return;
	}

	// copy exsited mesh property into vertices
	vertices.resize(pSize * 3 + nSize * 3 + tSize * 2);

	// would be slow, sad
	// not supported tangents now
	int vertexSize = 3;
	vertexSize += nSize > 0 ? 3 : 0;
	vertexSize += tSize > 0 ? 2 : 0;
	for (int i = 0; i < pSize; i++)
	{

		vertices[i * vertexSize + 0] = positions[i].x;
		vertices[i * vertexSize + 1] = positions[i].y;
		vertices[i * vertexSize + 2] = positions[i].z;

		if (nSize > 0)
		{
			vertices[i * vertexSize + 3] = normals[i].x;
			vertices[i * vertexSize + 4] = normals[i].y;
			vertices[i * vertexSize + 5] = normals[i].z;

			if (tSize > 0)
			{
				vertices[i * vertexSize + 6] = uvs[i].x;
				vertices[i * vertexSize + 7] = uvs[i].y;
			}
		}
		else if (tSize > 0)
		{
			vertices[i * vertexSize + 3] = uvs[i].x;
			vertices[i * vertexSize + 4] = uvs[i].y;
		}
	}

	// vao generation and bind
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	// vbo generation and bind
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(unsigned int), &triangles[0], GL_STATIC_DRAW);

	unsigned int vaIndex    = 0;
	unsigned int startIndex = 0;

	// vertex positions
	if (pSize > 0)
	{
		glEnableVertexAttribArray(vaIndex);
		glVertexAttribPointer(startIndex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		vaIndex++;
		startIndex++;
	}

	// vertex normals
	if (nSize > 0)
	{
		size_t offset = 3 * sizeof(float);
		glEnableVertexAttribArray(vaIndex);
		glVertexAttribPointer(startIndex, 3, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)offset);
		vaIndex++;
		startIndex++;
	}

	// vertex texture coords
	if (tSize > 0)
	{
		size_t offset = (nSize > 0 ? 6 : 3) * sizeof(float);
		glEnableVertexAttribArray(vaIndex);
		glVertexAttribPointer(startIndex, 2, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (void*)offset);
		vaIndex++;
		startIndex++;
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

