#pragma once
#include <core/log/s3Log.h>
#include <3d/s3Mesh.h>

void print(const std::vector<int>& list)
{
	for (auto i : list)
		s3Log::print("%d, ", i);
	s3Log::print("\n");
}

int main()
{
	s3Mesh mesh;
	std::vector<int> A = { 1, 1, 1, 1, 1, 1, 1 };
	std::vector<int> B = { 2, 2, 2, 2 };
	std::vector<int> C = { 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	std::vector<int> D = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

	print(A);
	print(B);
	print(C);
	print(D);

	mesh.setSubMeshCount(4);
	mesh.setTriangles(A, 0);
	print(mesh.triangles);

	mesh.setTriangles(C, 2);
	print(mesh.triangles);
	
	mesh.setTriangles(B, 1);
	print(mesh.triangles);
	
	mesh.setTriangles(D, 4);
	print(mesh.triangles);

	return 0;
}