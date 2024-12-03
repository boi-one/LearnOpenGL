#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CameraMovement
{
	Forward,
	Backward,
	Left,
	Right
};

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float yaw   = -90.0f;
	float pitch = 0.0f;

	float movementSpeed = 2.5f;
	float mouseSensitivity = 0.1f;
	float fov = 45.0f;
	bool firstMouse = true;

	Camera(glm::vec3 camPosition, glm::vec3 camUp, float camYaw, float camPitch)
	{
		position = camPosition;
		up = camUp;
		yaw = camYaw;
		pitch = camPitch;
		UpdateCameraVectors();
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(position, position + front, up);
	}

	void ProcessKeyboard(CameraMovement direction, float deltaTime)
	{
		float velocity = movementSpeed * deltaTime;
		switch (direction)
		{
		case CameraMovement::Forward:
		{
			position += front * velocity;
		}break;
		case CameraMovement::Backward:
		{
			position -= front * velocity;
		}break;
		case CameraMovement::Left:
		{
			position -= right * velocity;
		}break;
		case CameraMovement::Right:
		{
			position += right * velocity;
		}break;
		}
	}

	void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true)
	{
		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (constrainPitch)
		{
			if (pitch > 89.0f)
				pitch = 89.0f;
			if (pitch < -89.0f)
				pitch = -89.0f;
		}

		UpdateCameraVectors();
	}

	void ProcessMouseScroll(float yoffset)
	{
		fov -= (float)yoffset;
		if (fov < 1.0f)
			fov = 1.0f;
		if (fov > 90.0f)
			fov = 90.0f;
	}

private:
	void UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		this->front = glm::normalize(front);
		this->right = glm::normalize(glm::cross(this->front, worldUp));
		this->up = glm::normalize(glm::cross(this->right, this->front));
	}
};

