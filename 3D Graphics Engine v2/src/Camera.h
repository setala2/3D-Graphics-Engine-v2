#pragma once
#include <glm/glm.hpp>
#include "Input.h"

namespace as3d
{
	class Camera
	{
	public:
		Camera(const glm::mat4& projection, const Input& input);

		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }

		void OnUpdate(float deltaTime);

		void SetProjectionMatrix(const glm::mat4& projection);
		void Reset();

	public:
		constexpr static glm::vec3 defaultPosition = glm::vec3(0.0f, 0.0f, 5.0f);
		constexpr static glm::vec3 defaultRotation = glm::vec3(0.0f);
		constexpr static float defaultFOV = glm::radians(45.0f);

	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;

		glm::vec3 position;
		glm::vec3 rotation;	// as Euler angles

		float movementSpeed = 3.0f;
		float rotationSpeed = 30.0f;
		const Input& input;

	private:
		void MoveLeft(float deltaTime);
		void MoveRight(float deltaTime);
		void MoveForward(float deltaTime);
		void MoveBack(float deltaTime);
		void MoveUp(float deltaTime);
		void MoveDown(float deltaTime);

		void RotateLeft(float deltaTime);
		void RotateRight(float deltaTime);
		void RotateUp(float deltaTime);
		void RotateDown(float deltaTime);

		void UpdateViewMatrix();
	};
}