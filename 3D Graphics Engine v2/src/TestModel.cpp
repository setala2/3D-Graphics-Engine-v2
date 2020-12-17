#include "pch.h"
#include "TestModel.h"

namespace as3d
{
	TestModel::TestModel()
	{
		root = std::make_unique<Node>();

		float testVertices[]
		{
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// bottom left front	0	blue
			1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// bottom right front	1	magenta
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,		// top right front		2	white
			-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// top left front		3	cyan
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	// bottom left back		4	black
			1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,	// bottom right back	5	red
			1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,	// top right back		6	yellow
			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	// top left back		7	green
		};

		uint32_t testIndices[]
		{
			0,1,2,	// front face
			2,3,0,

			4,0,3,	// left face
			3,7,4,

			3,2,6,	// top face
			6,7,3,

			1,5,6,	// right face
			6,2,1,

			4,5,1,	// bottom face
			1,0,4,

			5,4,7,	// back face
			7,6,5
		};

		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		
		auto vbo = std::make_unique<VertexBuffer>(testVertices, sizeof(testVertices));
		auto vao = std::make_unique<VertexArray>();
		vao->AddBuffer(*vbo, layout);
		auto ibo = std::make_unique<IndexBuffer>(testIndices, sizeof(testIndices));

		meshes.push_back(std::make_unique<Mesh>(vbo, vao, ibo));
		root->meshes.push_back(meshes[0].get());
	}
}