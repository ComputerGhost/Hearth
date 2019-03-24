#include "ShaderProgram.hpp"

namespace Core
{
	namespace
	{
		static const char *default_fragment_shader =
			"#version 330 core\n"
			"out vec3 color;\n"
			"void main(){\n"
			" color = vec3(1,0,0);\n"
			"}";
		static const char *default_vertex_shader =
			"#version 330 core\n"
			"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
			"void main(){\n"
			" gl_Position.xyz = vertexPosition_modelspace;\n"
			" gl_Position.w = 1.0;\n"
			"}";
	}

	ShaderProgram::ShaderProgram()
	{
		id = glCreateProgram();
	}

	ShaderProgram::ShaderProgram(ShaderProgram &&src) :
		id(src.id)
	{
		src.id = 0;
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

	ShaderProgram getDefaultShaderProgram()
	{
		Shader fragment{ ShaderType::Fragment, default_fragment_shader };
		Shader vertex{ ShaderType::Vertex, default_vertex_shader };

		ShaderProgram program;
		program.attachShader(vertex);
		program.attachShader(fragment);
		program.linkProgram();
		program.detachShader(fragment);
		program.detachShader(vertex);

		return program;
	}
}