#include "s3Mesh.h"

s3Mesh::s3Mesh()
{}

s3Mesh::~s3Mesh()
{}

void s3Mesh::clear()
{
	indices.clear();
	vertices.clear();
	normals.clear();
	tangents.clear();
	uv.clear();
}