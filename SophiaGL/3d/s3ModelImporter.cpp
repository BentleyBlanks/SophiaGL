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
        return nullptr;
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        std::vector<unsigned int> indices;

        auto& shape = shapes[i];
        for (const auto& index : shape.mesh.indices)
        {
            mesh->positions.push_back(glm::vec3(attrib.vertices[3 * index.vertex_index + 0],
                                                attrib.vertices[3 * index.vertex_index + 1],
                                                attrib.vertices[3 * index.vertex_index + 2]));

            mesh->normals.push_back(glm::vec3(attrib.normals[3 * index.normal_index + 0],
                                              attrib.normals[3 * index.normal_index + 1],
                                              attrib.normals[3 * index.normal_index + 2]));

            mesh->uvs.push_back(glm::vec2(attrib.texcoords[2 * index.texcoord_index + 0],
                                          attrib.texcoords[2 * index.texcoord_index + 1]));
        }

        mesh->setTriangles(indices, i);
    }
    mesh->apply();

    s3Log::success("Model loaded successfully\n", path);
	return mesh;
}
