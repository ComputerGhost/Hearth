#pragma once

#include <glad/glad.h>

#include "Shader.hpp"

namespace Core
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &) = delete;
		ShaderProgram(ShaderProgram &&);
		~ShaderProgram();

		void attachShader(const Shader &shader);
		void detachShader(const Shader &shader);

		void linkProgram();
		void useProgram();

	private:
		GLuint id;
	};

	ShaderProgram getDefaultShaderProgram();
}
