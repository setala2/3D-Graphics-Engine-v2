#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Material.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include <vector>
#include <memory>

namespace as3d
{
	class Mesh
	{
	public:
		Mesh(std::unique_ptr<VertexBuffer>& vbo,
			std::unique_ptr<VertexArray>& vao,
			std::unique_ptr<IndexBuffer>& ibo);
		void Draw();

	private:
		const Material* material = nullptr; // A reference to a material owned by the model instance
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<IndexBuffer> ibo;
	};

	/*
	class Node
	{
	public:
		void Draw();

	private:
		glm::mat4 transform;

		glm::vec3 position;
		glm::quat orientation;

		std::vector<Node> children;
		
	private:
		void DrawControls(); // Draw the controls for this node. Called by Model::DrawControlWindow()

		friend class Model;
	};

	class Model
	{
	public:
		glm::vec3 GetPosition() const;
		void Draw(const Shader& shader);
		void DrawControlWindow(); // Draw the entire control window

	private:
		std::unique_ptr<Node> root;
		std::vector<std::unique_ptr<Mesh>> meshes;
		std::vector<std::unique_ptr<Material>> materials;
	};

	*/
}