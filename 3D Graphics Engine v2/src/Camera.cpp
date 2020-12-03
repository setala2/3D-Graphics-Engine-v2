#include "pch.h"
#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"

namespace as3d
{
	Camera::Camera(const glm::mat4& projection, const Input& input)
		: projectionMatrix(projection), viewMatrix(1.0f), input(input)
	{
		Reset();
	}

	void Camera::OnUpdate(float deltaTime)
	{
		if (input.IsKeyDown(Keycode::W))
			MoveUp(deltaTime);
		if (input.IsKeyDown(Keycode::A))
			MoveLeft(deltaTime);
		if (input.IsKeyDown(Keycode::S))
			MoveDown(deltaTime);
		if (input.IsKeyDown(Keycode::D))
			MoveRight(deltaTime);
	}

	void Camera::SetProjectionMatrix(const glm::mat4& projection)
	{
		projectionMatrix = projection;
	}

	void Camera::Reset()
	{
		position = defaultPosition;
		UpdateViewMatrix();
	}

	void Camera::MoveLeft(float deltaTime)
	{
		position.x -= deltaTime * movementSpeed;
		UpdateViewMatrix();
	}

	void Camera::MoveRight(float deltaTime)
	{
		position.x += deltaTime * movementSpeed;
		UpdateViewMatrix();
	}

	void Camera::MoveUp(float deltaTime)
	{
		position.y += deltaTime * movementSpeed;
		UpdateViewMatrix();
	}

	void Camera::MoveDown(float deltaTime)
	{
		position.y -= deltaTime * movementSpeed;
		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));
	}
}