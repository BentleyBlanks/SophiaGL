#include <3d/s3ModelImporter.h>
#include <3d/s3Mesh.h>

#include "tiny_obj_loader.h"


s3Mesh* s3ModelImporter::load(const char* path)
{
	auto mesh = new s3Mesh();

    s3Log::debug("Parsering model file: %s...\n", path);



    s3Log::success("Model loaded successfully\n", path);
	return mesh;
}
