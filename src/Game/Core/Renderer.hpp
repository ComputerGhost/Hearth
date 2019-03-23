#pragma once

#include <glad/glad.h>

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
		GLuint program_id;
	};
}