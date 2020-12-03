#pragma once
#include <unordered_map>
#include <glm/glm.hpp>

namespace as3d
{
	class Shader
	{
		uint32_t handle;

	public:
		Shader(const char* vertexFile, const char* fragmentFile);
		~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void Bind();
		void Unbind();

		/*
			Uniform methods
		*/

		void SetInt32(const std::string& uniformName, int32_t value) const;
		void SetVector3(const std::string& uniformName, const glm::vec3& value) const;
		void SetMatrix4(const std::string& uniformName, const glm::mat4& value) const;

	private:
		void Compile(const char* vertexFile, const char* fragmentFile);
		mutable std::unordered_map<std::string, int32_t> uniformCache;

		int32_t GetUniformLocation(const std::string& uniformName) const;
	};
}