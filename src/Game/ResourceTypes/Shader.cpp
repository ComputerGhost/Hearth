#include <memory>
#include <stdexcept>

#include "Shader.hpp"

namespace ResourceTypes
{
	Shader::Shader(ShaderType type, const char *source)
	{
		if (type == ShaderType::Fragment)
			id = glCreateShader(GL_FRAGMENT_SHADER);
		else if (type == ShaderType::Vertex)
			id = glCreateShader(GL_VERTEX_SHADER);

		if (id == 0)
			throw std::runtime_error("Could not create shader.");

		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		// Check status and throw an exception if failed.
		GLint status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			auto log = std::make_unique<char[]>(length);
			glGetShaderInfoLog(id, length, &length, log.get());
			throw std::runtime_error(log.get());
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}
}