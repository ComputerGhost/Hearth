#include "ShaderProgram.hpp"

namespace ResourceTypes
{

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram()
	{
		if (id > 0)
			glDeleteProgram(id);
	}

	void ShaderProgram::attachShader(const Shader &shader)
	{
		glAttachShader(id, shader.id);
	}

	void ShaderProgram::detachShader(const Shader &shader)
	{
		glDetachShader(id, shader.id);
	}

	void ShaderProgram::linkProgram()
	{
		glLinkProgram(id);
	}

	void ShaderProgram::useProgram()
	{
		glUseProgram(id);
	}
}