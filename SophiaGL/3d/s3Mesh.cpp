#include <3d/s3Mesh.h>
#include <glad/glad.h>
#include <3d/s3VertexData.h>

// ---------------------------------------------s3Submesh---------------------------------------------
// Calculated in cpp instead of lua. Beacause size may different between different platform. 
std::size_t getDataTypeSize(semantic_data_type data_type)
{
	switch (data_type)
	{
	case eDT_INVALID:
		return 0;
	case eDT_FLOAT:
		return sizeof(float);
	case eDT_INT:
		return sizeof(int);
	case eDT_BOOL:
		return sizeof(bool);
	case eDT_HALF:
		// 16 bits float not supported
		return sizeof(float);
	case eDT_SHORT:
		return sizeof(short);
	case eDT_UINT:
		return sizeof(unsigned int);
	}
	return 0;
}

GLsizei ConvertDataTypeToGLType(semantic_data_type data_type)
{
	switch (data_type)
	{
	case eDT_INVALID:
		return 0;
	case eDT_FLOAT:
		return GL_FLOAT;
	case eDT_INT:
		return GL_INT;
	case eDT_BOOL:
		return GL_BOOL;
	case eDT_HALF:
		// 16 bits float not supported
		//return GL_HALF_FLOAT;
		return GL_FLOAT;
	case eDT_SHORT:
		return GL_SHORT;
	case eDT_UINT:
		return GL_UNSIGNED_INT;
	}
	return 0;
}

s3Submesh::~s3Submesh()
{
	if (vbo != 0)
	{
		glDeleteBuffers(1, &vbo);
		vbo = 0;
	}
	if (ebo != 0)
	{
		glDeleteBuffers(1, &ebo);
		ebo = 0;
	}
	if (vao != 0)
	{
		glDeleteBuffers(1, &vao);
		vao = 0;
	}
}

void s3Submesh::clear()
{
	indices.clear();
	positions.clear();
	normals.clear();
	tangents.clear();
	texCoord0.clear();
}

void s3Submesh::updateVertexStream(unsigned int handle)
{
	auto& manager = s3InputLayoutManager::getInstance();
	if(!manager.isValid(handle))
	{
		s3Log::warning("s3Submesh's related handle not valid\n");
		return;
	}

	// input layout's equality check only happens between handle
	if (handle == inputLayoutHandle) return;

	int pCount  = (int)positions.size();
	int nCount  = (int)normals.size();
	int cCount  = (int)colors.size();
	int t0Count = (int)texCoord0.size();
	int t1Count = (int)texCoord1.size();
	int t2Count = (int)texCoord2.size();
	int t3Count = (int)texCoord3.size();
	int tCount  = (int)tangents.size();
	if (pCount < 0/* || pCount != vertexCount*/)
	{
		s3Log::warning("s3Submesh's position properties error\n");
		return;
	}

	auto& inputLayout = manager.get(handle);
	auto newVertexStride = 0;
	for (int i = 0; i < semantic_channel::eC_COUNT; i++)
	{
		if (!inputLayout.channels[i]) continue;

		auto dataSize = getDataTypeSize(inputLayout.dataTypes[i]);
		auto dimension = inputLayout.dimensions[i];

		newVertexStride += (unsigned int)(dataSize * dimension);
	}

	// Reallocate CPU / GPU resources
	if (!bIsInited || newVertexStride != vertexStride)
	{
		vertexStride = newVertexStride;
		S3_SAFE_FREE(vertexStream);

		unsigned int verticesLength = vertexStride * vertexCount;
		vertexStream = malloc(verticesLength);
		// if no related semantic was found, use 0 instead
		memset(vertexStream, 0, verticesLength);
	}

	// Update mesh data into vertex stream
	char* vertexPtr = (char*)vertexStream;
	for (unsigned int i = 0; i < vertexCount; i++)
	{
		int offset = 0;
		for (int j = 0; j < semantic_channel::eC_COUNT; j++)
		{
			if (!inputLayout.channels[j]) continue;

			auto dataTypeSize = (unsigned)getDataTypeSize(inputLayout.dataTypes[j]);
			auto dimension = inputLayout.dimensions[j];

			switch (j)
			{
			case eC_VERTEX:
				memcpy(vertexPtr + i * vertexStride + offset, &(positions[i][0]), dimension * dataTypeSize);
				break;
			case eC_NORMAL:
				memcpy(vertexPtr + i * vertexStride + offset, &(normals[i][0]), dimension * dataTypeSize);
				break;
			case eC_COLOR:
				memcpy(vertexPtr + i * vertexStride + offset, &(colors[i][0]), dimension * dataTypeSize);
				break;
			case eC_TEXCOORD0:
				memcpy(vertexPtr + i * vertexStride + offset, &(texCoord0[i][0]), dimension * dataTypeSize);
				break;
			case eC_TEXCOORD1:
				memcpy(vertexPtr + i * vertexStride + offset, &(texCoord1[i][0]), dimension * dataTypeSize);
				break;
			case eC_TEXCOORD2:
				memcpy(vertexPtr + i * vertexStride + offset, &(texCoord2[i][0]), dimension * dataTypeSize);
				break;
			case eC_TEXCOORD3:
				memcpy(vertexPtr + i * vertexStride + offset, &(texCoord3[i][0]), dimension * dataTypeSize);
				break;
			case eC_TANGENT:
				memcpy(vertexPtr + i * vertexStride + offset, &(tangents[i][0]), dimension * dataTypeSize);
				break;
			}

			offset += dimension * dataTypeSize;
		}
	}

	// vao generation and bind
	// vbo, vertex buffer
	// ebo, index buffer
	if (vao == 0) glGenVertexArrays(1, &vao);
	if (vbo == 0) glGenBuffers(1, &vbo);
	if (ebo == 0) glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	if (bIsInited)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertexStride * vertexCount, vertexStream);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.size() * sizeof(unsigned int), &indices[0]);
	}
	else
	{
		// Ref: https://community.khronos.org/t/will-glbufferdata-leak-memory/66421 
		// For modifying the data in the buffer object, use glBufferSubData or glMapBufferRange functions
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertexStride * vertexCount, vertexStream, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}

	// input layout
	int index = 0;
	unsigned long long attrOffset = 0;

	for (int i = 0; i < semantic_channel::eC_COUNT; i++)
	{
		if (!inputLayout.channels[i]) continue;

		auto dataSize = (int)getDataTypeSize(inputLayout.dataTypes[i]);
		auto dimension = inputLayout.dimensions[i];
		auto glDataType = ConvertDataTypeToGLType(inputLayout.dataTypes[i]);
		auto stride = dataSize * dimension;

		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, dimension, glDataType, GL_FALSE, vertexStride, (void*)attrOffset);

		attrOffset += (int)stride;
		index++;
	}

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	inputLayoutHandle = handle;
	bIsInited = true;
}

// ---------------------------------------------s3Mesh---------------------------------------------
//--! ref: https://docs.unity3d.com/2017.4/Documentation/ScriptReference/Mesh.html
s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	for (auto submesh : submeshes)
	{
		submesh->clear();
		S3_SAFE_DELETE(submesh);
	}

	submeshes.clear();
}

//void s3Mesh::setTriangles(const std::vector<unsigned int>& subIndices, int submesh)
//{
//	if (submesh < 0 || submesh >= indexRangeList.channelCount())
//	{
//		s3Log::warning("s3Mesh::setTriangles() invalid submesh index: %d\n", submesh);
//		return;
//	}
//
//	int newCount = (int)subIndices.channelCount();
//	auto& range = indexRangeList[submesh];
//
//	// std::copy won't alloc mem when exceeded, ensure enough space mannually
//	std::vector<unsigned int> temp;
//	auto tempSize = indices.channelCount() - range.start - range.count;
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
//	indices.resize(indices.channelCount() + diffCount);
//
//	auto subIndicesStart = indices.begin() + range.start;
//	std::copy(subIndices.begin(), subIndices.end(), subIndicesStart);
//
//	// update range list
//	range.count = newCount;
//	updateRangeList();
//
//	if (temp.channelCount() > 0)
//	{
//		auto copyBackStart = indices.begin() + range.start + newCount;
//		std::copy(temp.begin(), temp.end(), copyBackStart);
//	}
//}
//
//void s3Mesh::setSubMeshCount(int subMeshCount)
//{
//	int currentCount = (int)indexRangeList.channelCount();
//	indexRangeList.resize(subMeshCount);
//	updateRangeList();
//}
//
//void s3Mesh::updateRangeList()
//{
//	if (indexRangeList.channelCount() <= 0) return;
//
//	auto lastRange = indexRangeList[0];
//	for (int i = 1; i < indexRangeList.channelCount(); i++)
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
//	if (submesh < 0 || submesh >= indexRangeList.channelCount())
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
void s3Mesh::updateVertexStream(unsigned int handle)
{
	for (auto submesh : submeshes)
	{
		// Update submesh's vertex stream if possible
		submesh->updateVertexStream(handle);
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

