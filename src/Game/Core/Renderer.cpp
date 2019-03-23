#include "Renderer.hpp"

namespace Core
{
	namespace
	{
		static const GLfloat vertex_buffer_data[] = {
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f,  1.0f, 0.0f,
		};

		static const char *vertex_shader =
			"#version 330 core\n"
			"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
			"void main(){\n"
			" gl_Position.xyz = vertexPosition_modelspace;\n"
			" gl_Position.w = 1.0;\n"
			"}";

		static const char *fragment_shader =
			"#version 330 core\n"
			"out vec3 color;\n"
			"void main(){\n"
			" color = vec3(1,0,0);\n"
			"}";
	}

	Renderer::Renderer()
	{
		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);

		GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vsId, 1, &vertex_shader, NULL);
		glCompileShader(vsId);

		GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fsId, 1, &fragment_shader, NULL);
		glCompileShader(fsId);

		program_id = glCreateProgram();
		glAttachShader(program_id, vsId);
		glAttachShader(program_id, fsId);
		glLinkProgram(program_id);

		glDetachShader(program_id, vsId);
		glDetachShader(program_id, fsId);
		glDeleteShader(fsId);
		glDeleteShader(fsId);
	}

	void Renderer::render(double elapsed_time)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(program_id);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
}