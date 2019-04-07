#pragma once

#include <glad/glad.h>

#include "ShaderType.hpp"

namespace ResourceTypes
{
	class Shader
	{
		friend class ShaderProgram;
	public:
		Shader() = delete;
		Shader(const Shader &) = delete;
		explicit Shader(ShaderType type, const char *source);
		~Shader();
	private:
		GLuint id = 0;
	};
}