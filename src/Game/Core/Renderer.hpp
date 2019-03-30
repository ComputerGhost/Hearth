#pragma once

#include <glad/glad.h>

#include "ShaderProgram.hpp"

namespace Core
{
	class Renderer
	{
	public:
		Renderer();

		void render(double elapsed_time);

	private:
		// temporary junk while we test stuff out
		GLuint vertex_array_id;
		GLuint vertex_buffer;
		ShaderProgram program;
	};
}