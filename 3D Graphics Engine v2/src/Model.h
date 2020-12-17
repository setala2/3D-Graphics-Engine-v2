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
	// The abstract model class. User must implement their own subclass that can load or generate themselves however they like.
	// The structure of the base class resembles the structure used in Assimp, since we will eventually be using that to load our models.
	// A model contains a tree of nodes, as well as a set of meshes and a set of materials.
	// Nodes represent transformations and reference one or more meshes owned by the model.
	// Meshes represent the actual geometry that gets drawn. Each mesh should reference a single material owned by the model.
	class Model
	{
	protected:
		class Mesh
		{
		public:
			Mesh(std::unique_ptr<VertexBuffer>& vbo,
				std::unique_ptr<VertexArray>& vao,
				std::unique_ptr<IndexBuffer>& ibo);
			void Draw() const;

		private:
			const Material* material = nullptr; // A reference to a material owned by the model instance
			std::unique_ptr<VertexBuffer> vbo;
			std::unique_ptr<VertexArray> vao;
			std::unique_ptr<IndexBuffer> ibo;
		};

		class Node
		{
		public:
			void Draw(const Shader& shader, const glm::mat4& accumulatedTransform) const;
			//void DrawControls(); // Draw the controls for this node. Called by Model::DrawControlWindow()
			void UpdateModelMatrix();

		public:
			glm::mat4 modelMatrix = glm::mat4(1.0f);

			glm::vec3 position = glm::vec3(0.0f);
			glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

			std::vector<Node> children;
			std::vector<const Mesh*> meshes;	// References to meshes owned by the model
		};

	public:
		virtual ~Model() = default;
		glm::vec3 GetPosition() const { return root->position; }
		void Draw(const Shader& shader) const;
		//void DrawControlWindow(); // Draw the entire control window

	protected:
		Model() = default;
		std::unique_ptr<Node> root;
		// The mesh and material vectors store unique_ptrs instead of the mesh and material instances
		// because we reference the stored meshes and materials via pointers in the Node and Mesh classes.
		// The additional indirection should make it safe, even if the vector moves somewhere else.
		std::vector<std::unique_ptr<Mesh>> meshes;		  
		std::vector<std::unique_ptr<Material>> materials; 
	};

}
