#include <graphics/s3Renderer.h>
#include <graphics/s3Material.h>
#include <3d/s3Mesh.h>
#include <app/s3Window.h>
#include <glad/glad.h>

bool s3Renderer::bDepthTest = false;

void s3Renderer::setDepthTest(bool _bDepthTest)
{
	bDepthTest = _bDepthTest;

	if (bDepthTest)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void s3Renderer::clear(glm::vec4 clearColor, bool color, bool depth)
{
	glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst)
{
}

void s3Renderer::blit(s3Texture& src, s3RenderTexture& dst, const s3Material& material)
{
}

void s3Renderer::setRenderTarget(const s3RenderTexture& rt)
{
}

void s3Renderer::drawMesh(const s3Mesh& mesh, const s3Material& material)
{
	auto shader = material.getShader();
	shader.begin();

	for (auto submesh : mesh.submeshes)
	{
		// update mesh's vertex stream with shader's inputlayout
		submesh->updateVertexStream(shader.getInputLayoutHandle());

		// draw mesh
		glBindVertexArray(submesh->vao);
		glDrawElements(GL_TRIANGLES, (int)submesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	shader.end();
}
