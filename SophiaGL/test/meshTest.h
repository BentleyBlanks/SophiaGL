#pragma once
#include <core/log/s3Log.h>
#include <3d/s3ModelImporter.h>
#include <3d/s3Mesh.h>
#include <app/s3Window.h>

void print(const std::vector<unsigned int>& list)
{
	for (auto i : list)
		s3Log::print("%d, ", i);
	s3Log::print("\n");
}

int main()
{
	s3Mesh mesh;
#if 0
	std::vector<unsigned int> A = { 1, 1, 1, 1, 1, 1, 1 };
	std::vector<unsigned int> B = { 2, 2, 2, 2 };
	std::vector<unsigned int> C = { 3, 3, 3, 3, 3, 3, 3, 3, 3 };
	std::vector<unsigned int> D = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };

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
	
	mesh.setTriangles(D, 3);
	print(mesh.triangles);
#endif

#if 0
	s3Window& window = s3Window::getInstance();
	window.init("SophiaGL", 100, 100, 1280, 720);

	mesh.triangles.resize(3);

	std::vector<glm::vec3> p = { glm::vec3(1, 1, 1), glm::vec3(2, 2, 2), glm::vec3(3, 3, 3) };
	std::vector<glm::vec3> n = { glm::vec3(4, 4, 4), glm::vec3(5, 5, 5), glm::vec3(6, 6, 6) };
	std::vector<glm::vec2> t = { glm::vec2(7, 7), glm::vec2(8, 8), glm::vec2(9, 9) };
	mesh.positions = p;
	mesh.normals   = n;
	mesh.uvs       = t;
	mesh.apply();
#endif

	s3Mesh* mesh = s3ModelImporter::load("../../resources/models/cube/cube.obj");

	return 0;
}