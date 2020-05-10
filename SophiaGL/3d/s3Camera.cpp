#include <3d/s3Camera.h>
#include <app/s3CallbackManager.h>
#include <core/s3Event.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//--! ref: https://docs.unity3d.com/ScriptReference/Camera.html
class s3CameraHandler : public s3CallbackHandle
{
public:
	s3CameraHandler(s3Camera* camera) : camera(camera)
	{}

	void onHandle(const s3CallbackUserData* userData)
	{
		if (userData->sender == &s3CallbackManager::onKeyPressed)
		{
		    s3KeyEvent* keyEvent = (s3KeyEvent*)userData->data;
		    //keyEvent->print();

			glm::vec3& up        = camera->up;
			glm::vec3& position  = camera->position;
			glm::vec3& direction = camera->direction;
			float speed          = camera->speed;

			// control key
			if (keyEvent->shift)
				speed = 5 * speed;

			// move key
			if(keyEvent->keyType == s3KeyType::W)
				position += speed * direction;
			else if (keyEvent->keyType == s3KeyType::S)
				position -= speed * direction;
			else if (keyEvent->keyType == s3KeyType::A)
				position -= glm::normalize(glm::cross(direction, up)) * speed;
			else if (keyEvent->keyType == s3KeyType::D)
				position += glm::normalize(glm::cross(direction, up)) * speed;
		}
		else if (userData->sender == &s3CallbackManager::onKeyReleased)
		{
			s3KeyEvent* keyEvent = (s3KeyEvent*)userData->data;
			//keyEvent->print();
		}
		else if (userData->sender == &s3CallbackManager::onMouseScrolled)
		{
			s3MouseEvent* mouseEvent = (s3MouseEvent*)userData->data;
			s3Log::debug("Scroll: %f\n", mouseEvent->scroll);

			float& fov = camera->fov;
			fov -= mouseEvent->scroll;
			
			if (fov <= 1.0f)
				fov = 1.0f;
			if (fov >= 90.0f)
				fov = 90.0f;
		}
		else if (userData->sender == &s3CallbackManager::onMouseMoved)
		{
			s3MouseEvent* mouseEvent = (s3MouseEvent*)userData->data;

			// change camera view only when right mouse button pressed
			if (mouseEvent->type != s3MouseType::right) return;

			float& yaw         = camera->yaw;
			float& pitch       = camera->pitch;
			float& sensitivity = camera->sensitivity;

			float offsetX = (float)mouseEvent->offsetX;
			float offsetY = (float)mouseEvent->offsetY;
			s3Log::debug("OffsetX: %f, OffsetY: %f\n", offsetX, offsetY);
			//s3Log::debug("Yaw: %f, Pitch: %f\n", yaw, pitch);

			offsetX *= sensitivity;
			offsetY *= sensitivity;

			yaw   += offsetX;
			pitch += offsetY;

			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;

			glm::vec3 direction;
			direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			direction.y = sin(glm::radians(pitch));
			direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			camera->direction = glm::normalize(direction);
		}
	}

	s3Camera* camera;
};

s3Camera::s3Camera()
{
	handler = new s3CameraHandler(this);
	s3CallbackManager::onKeyPressed    += *handler;
	s3CallbackManager::onKeyReleased   += *handler;
	s3CallbackManager::onMouseMoved    += *handler;
	s3CallbackManager::onMouseScrolled += *handler;
}

s3Camera::~s3Camera()
{
	s3CallbackManager::onKeyPressed    -= *handler;
	s3CallbackManager::onKeyReleased   -= *handler;
	s3CallbackManager::onMouseMoved    -= *handler;
	s3CallbackManager::onMouseScrolled -= *handler;
	S3_SAFE_DELETE(handler);
}

glm::mat4 s3Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + direction, up);
}

glm::mat4 s3Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
}
