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

};