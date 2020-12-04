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
			MoveForward(deltaTime);
		if (input.IsKeyDown(Keycode::A))
			MoveLeft(deltaTime);
		if (input.IsKeyDown(Keycode::S))
			MoveBack(deltaTime);
		if (input.IsKeyDown(Keycode::D))
			MoveRight(deltaTime);
		if (input.IsKeyDown(Keycode::E))
			MoveUp(deltaTime);
		if (input.IsKeyDown(Keycode::Q))
			MoveDown(deltaTime);

		if (input.IsKeyDown(Keycode::Left))
			RotateLeft(deltaTime);
		if (input.IsKeyDown(Keycode::Right))
			RotateRight(deltaTime);
		if (input.IsKeyDown(Keycode::Up))
			RotateUp(deltaTime);
		if (input.IsKeyDown(Keycode::Down))
			RotateDown(deltaTime);
	}

	void Camera::SetProjectionMatrix(const glm::mat4& projection)
	{
		projectionMatrix = projection;
	}

	void Camera::Reset()
	{
		position = defaultPosition;
		rotation = defaultRotation;
		UpdateViewMatrix();
	}

	void Camera::MoveLeft(float deltaTime)
	{
		position.x -= std::cosf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		position.z -= std::sinf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::MoveRight(float deltaTime)
	{
		position.x += std::cosf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		position.z += std::sinf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::MoveForward(float deltaTime)
	{
		position.x += std::sinf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		position.z -= std::cosf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::MoveBack(float deltaTime)
	{
		position.x -= std::sinf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
		position.z += std::cosf(glm::radians(rotation.y)) * movementSpeed * deltaTime;
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

	void Camera::RotateLeft(float deltaTime)
	{
		rotation.y -= rotationSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::RotateRight(float deltaTime)
	{
		rotation.y += rotationSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::RotateUp(float deltaTime)
	{
		rotation.x -= rotationSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::RotateDown(float deltaTime)
	{
		rotation.x += rotationSpeed * deltaTime;
		UpdateViewMatrix();
	}

	void Camera::UpdateViewMatrix()
	{
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		viewMatrix = glm::translate(rotationMatrix, glm::vec3(-position.x, -position.y, -position.z));
	}
}