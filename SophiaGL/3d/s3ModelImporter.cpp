#include <3d/s3ModelImporter.h>
#include <3d/s3Mesh.h>

#include <tiny_obj_loader.h>


s3Mesh* s3ModelImporter::load(const char* path)
{
	auto mesh = new s3Mesh();
    s3Log::debug("Parsering model file: %s...\n", path);

    // TinyObjLoader
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error, warning;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warning, &error, path);

    if (!error.empty() || !warning.empty())
    {
        s3Log::warning("Model loading warning: %s\n", warning.c_str(), error.c_str());
    }

    if (!ret)
    {
        s3Log::error("Model loading failed\n");
        return false;
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        std::vector<unsigned int> indices;

        mesh->setTriangles(indices, i);
    }

    s3Log::success("Model loaded successfully\n", path);
	return mesh;
}
