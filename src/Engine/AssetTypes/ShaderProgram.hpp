#pragma once

#include <glad/glad.h>

#include "Shader.hpp"

namespace Hearth::AssetTypes
{
	class ShaderProgram
	{
	public:
		ShaderProgram();
		ShaderProgram(const ShaderProgram &) = delete;
		~ShaderProgram();

		void attachShader(const Shader &shader);
		void detachShader(const Shader &shader);

		void linkProgram();
		void useProgram() const;

		GLuint getUniformLocation(const char *name);

	private:
		GLuint id;
	};
}
