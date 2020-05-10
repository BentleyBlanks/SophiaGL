#include <3d/s3ModelImporter.h>
#include <3d/s3Mesh.h>

#include "tiny_obj_loader.h"


s3Mesh* s3ModelImporter::load(const char* path)
{
	auto mesh = new s3Mesh();

    s3Log::debug("Parsering model file: %s...\n", path);

    // TinyObjLoader
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    std::string xx(path);

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, xx);

    if (!err.empty())
        s3Log::warning("Warning: %s\n", err.c_str());

    if (!ret)
    {
        s3Log::error("Model loading failed\n");
        return nullptr;
    }

    for (const auto& shape : shapes)
    {
        s3Mesh* mesh = new s3Mesh();

        // Mesh
        std::vector<s3VertexPNT> vertices;
        std::vector<uint32> indices;

        for (const auto& index : shape.mesh.indices)
        {
            s3VertexPNT vertex;

            vertex.position = t3Vector3f(attrib.vertices[3 * index.vertex_index + 0],
                                         attrib.vertices[3 * index.vertex_index + 1],
                                         attrib.vertices[3 * index.vertex_index + 2]);

            vertex.normal = t3Vector3f(attrib.normals[3 * index.normal_index + 0],
                                       attrib.normals[3 * index.normal_index + 1],
                                       attrib.normals[3 * index.normal_index + 2]);

            vertex.textureCoordinate = t3Vector2f(attrib.texcoords[2 * index.texcoord_index + 0],
                                                  attrib.texcoords[2 * index.texcoord_index + 1]);

            vertices.push_back(vertex);
            indices.push_back((int32)indices.size());
        }

        mesh->name = shape.name;
        mesh->indexCountList = (int32)indices.size();

        ID3D11Device* device;
        deviceContext->GetDevice(&device);

        s3CreateBuffer(device, vertices, D3D11_BIND_VERTEX_BUFFER, &mesh->vertexBuffer);
        s3CreateBuffer(device, indices, D3D11_BIND_INDEX_BUFFER, &mesh->indexBuffer);

        meshes.push_back(mesh);
    }

    s3Log::success("Model loaded successfully\n", path);
	return mesh;
}
