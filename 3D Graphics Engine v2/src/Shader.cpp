#include "pch.h"
#include "Shader.h"
#include "FileReader.h"

namespace as3d
{
	Shader::Shader(const char* vertexFile, const char* fragmentFile)
	{
		Compile(vertexFile, fragmentFile);
	}

	Shader::~Shader()
	{
		glDeleteProgram(handle);
	}

	void Shader::Bind()
	{
		glUseProgram(handle);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}

	/*void Shader::SetInt32(const std::string& uniformName, int32_t value) const
	{
		glUniform1i(GetUniformLocation(uniformName), value);
	}

	void Shader::SetVector3(const std::string& uniformName, const glm::vec3& value) const
	{
		glUniform3f(GetUniformLocation(uniformName), value[0], value[1], value[2]);
	}

	void Shader::SetMatrix4(const std::string& uniformName, const glm::mat4& value) const
	{
		glUniformMatrix4fv(GetUniformLocation(uniformName), 1, GL_FALSE, &(value[0][0]));
	}*/

	void Shader::Compile(const char* vertexFile, const char* fragmentFile)
	{
		std::string vertexSource = utility::ReadTextFile(vertexFile);
		std::string fragmentSource = utility::ReadTextFile(fragmentFile);

		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const GLchar* source = (const GLchar*)vertexSource.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			std::cerr << "Vertex shader compilation error:\n"
				<< infoLog.data() << '\n';

			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const GLchar*)fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);


			std::cerr << "Fragment shader compilation error:\n"
				<< infoLog.data() << '\n';

			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		GLuint program = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			std::cerr << "Shader linking error:\n"
				<< infoLog.data() << '\n';

			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

		// Remember the gl generated handle
		this->handle = program;
	}

	int32_t Shader::GetUniformLocation(const std::string& uniformName) const
	{
		if (uniformCache.find(uniformName) != uniformCache.end())
			return uniformCache.at(uniformName);

		int32_t uniformLocation = glGetUniformLocation(handle, uniformName.c_str());
		uniformCache.insert({ uniformName, uniformLocation });
		return uniformLocation;
	}
}