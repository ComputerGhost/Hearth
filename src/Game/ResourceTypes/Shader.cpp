#include <cassert>

#include "Shader.hpp"

namespace ResourceTypes
{
	Shader::Shader(ShaderType type, const char *source)
	{
		if (type == ShaderType::Fragment)
			id = glCreateShader(GL_FRAGMENT_SHADER);
		else if (type == ShaderType::Vertex)
			id = glCreateShader(GL_VERTEX_SHADER);
		else
			assert(false && "The shader type doesn't exist.");

		glShaderSource(id, 1, &source, NULL);
		glCompileShader(id);

		GLint status;
		glGetShaderiv(id, GL_COMPILE_STATUS, &status);
		if (status == GL_FALSE) {
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &status);
			auto entry = new char[status];
			glGetShaderInfoLog(id, status, &status, entry);
			delete[] entry;
		}
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}
}