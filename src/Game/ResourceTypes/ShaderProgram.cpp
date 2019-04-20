#include <memory>
#include <stdexcept>

#include "ShaderProgram.hpp"

namespace ResourceTypes
{

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
		if (id == 0)
			throw std::runtime_error("Could not create shader program.");
	}

	ShaderProgram::~ShaderProgram()
	{
		if (id > 0)
			glDeleteProgram(id);
	}

	void ShaderProgram::attachShader(const Shader &shader)
	{
		glAttachShader(id, shader.id);
		if (glGetError() == GL_INVALID_OPERATION)
			throw std::runtime_error("Could not attach shader.");
	}

	void ShaderProgram::detachShader(const Shader &shader)
	{
		glDetachShader(id, shader.id);
	}

	void ShaderProgram::linkProgram()
	{
		glLinkProgram(id);

		// Check status and throw an exception if failed.
		GLint status;
		glGetProgramiv(id, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint length;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
			auto log = std::make_unique<char>(length);
			glGetProgramInfoLog(id, length, &length, log.get());
			throw std::runtime_error(log.get());
		}
	}

	void ShaderProgram::useProgram() const
	{
		glUseProgram(id);
	}

	GLuint ShaderProgram::getUniformLocation(const char *name)
	{
		return glGetUniformLocation(id, name);
	}
}