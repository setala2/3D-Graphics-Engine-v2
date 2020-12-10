#include "pch.h"
#include "Model.h"

namespace as3d
{
	Mesh::Mesh(std::unique_ptr<VertexBuffer>& vbo,
		std::unique_ptr<VertexArray>& vao,
		std::unique_ptr<IndexBuffer>& ibo)
		: vbo(std::move(vbo)), vao(std::move(vao)), ibo(std::move(ibo))
	{	}

	void Mesh::Draw()
	{
		vao->Bind();
		ibo->Bind();
		glDrawElements(GL_TRIANGLES, ibo->GetCount(), ibo->GetType(), NULL);
	}
}