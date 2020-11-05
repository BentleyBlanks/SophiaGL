#include <3d/s3ModelImporter.h>
#include <3d/s3Mesh.h>

#include <tiny_obj_loader.h>

s3Mesh* s3ModelImporter::load(const char* path)
{
	auto mesh = new s3Mesh();
    s3Log::debug("Parsering model file: %s...\n", path);

    // tiny obj loader
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

    //--! ref: https://github.com/tinyobjloader/tinyobjloader/blob/master/examples/viewer/viewer.cc
    for (int i = 0; i < shapes.size(); i++)
    {
        auto& shape = shapes[i];
        auto submesh = new s3Submesh(shape.name);
        for (const auto& index : shape.mesh.indices)
        {
            // -1 means not used
            if (attrib.vertices.size() > 0 && index.vertex_index != -1)
            {
				glm::vec3 position = glm::vec3(attrib.vertices[3 * index.vertex_index + 0],
											   attrib.vertices[3 * index.vertex_index + 1],
											   attrib.vertices[3 * index.vertex_index + 2]);

                submesh->positions.push_back(position);
            }

            if (attrib.normals.size() > 0 && index.normal_index != -1)
            {
                glm::vec3 normal = glm::vec3(attrib.normals[3 * index.normal_index + 0],
                                             attrib.normals[3 * index.normal_index + 1],
                                             attrib.normals[3 * index.normal_index + 2]);
                submesh->normals.push_back(normal);
            }

            if (attrib.texcoords.size() > 0 && index.texcoord_index != -1)
            {
                glm::vec2 uv = glm::vec2(attrib.texcoords[2 * index.texcoord_index + 0],
                                         attrib.texcoords[2 * index.texcoord_index + 1]);

                submesh->texCoord0.push_back(uv);
            }

            //mesh->vertices.push_back(vertex);
            submesh->indices.push_back((unsigned int)submesh->indices.size());
        }
        mesh->submeshes.push_back(submesh);
    }
    mesh->apply();

    s3Log::success("Model loaded successfully\n", path);
	return mesh;
}
