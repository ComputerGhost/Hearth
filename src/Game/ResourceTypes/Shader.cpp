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
	}

	Shader::~Shader()
	{
		glDeleteShader(id);
	}
}