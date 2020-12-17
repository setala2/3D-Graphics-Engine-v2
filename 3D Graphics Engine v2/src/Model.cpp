#include "pch.h"
#include "Model.h"

namespace as3d
{
	Model::Mesh::Mesh(std::unique_ptr<VertexBuffer>& vbo,
		std::unique_ptr<VertexArray>& vao,
		std::unique_ptr<IndexBuffer>& ibo)
		: vbo(std::move(vbo)), vao(std::move(vao)), ibo(std::move(ibo))
	{	}

	void Model::Mesh::Draw() const
	{
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetType(), NULL);
	}

	void Model::Node::Draw(const Shader& shader, const glm::mat4& accumulatedTransform) const
	{
		// Add this node's own transform to the so far accumulated transform.
		// We need to make a new matrix instead of taking accumulatedTransform as a non-const reference and updating it,
		// because we want to draw all of the child nodes recursively and using the same transform for all of them
		glm::mat4 thisTransform = accumulatedTransform * modelMatrix;

		shader.SetMatrix4("modelMatrix", thisTransform);
		for (auto& mesh : meshes)
			mesh->Draw();

		for (auto& child : children)
			child.Draw(shader, thisTransform);
	}

	void Model::Node::UpdateModelMatrix()
	{
		glm::mat4 rotationMatrix = glm::mat4_cast(orientation);
		modelMatrix = glm::translate(rotationMatrix, position);
	}

	void Model::Draw(const Shader& shader) const
	{
		shader.Bind();
		root->Draw(shader, glm::mat4(1.0f));
	}
}
