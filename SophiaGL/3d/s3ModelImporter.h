#pragma once
#include <core/s3Settings.h>

class s3Mesh;
class s3ModelImporter
{
public:
	// add some load config in the future
	static s3Mesh& load(const std::string& path);
};