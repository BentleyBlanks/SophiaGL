#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class s3Camera
{
public:
	s3Camera();
	~s3Camera();

	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;

	float speed    = 0.01666f, sensitivity = 0.12f;
	float fov      = 45.0f, aspectRatio = 1.3333f;
	float yaw      = -90.0f, pitch = 0.0f;
	float nearClip = 0.1f, farClip = 1000.0f;

	glm::vec3 up        = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 position  = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 1.0f);

private:
	class s3CameraHandler* handler;
};