#include "../ResourceTypes/Shader.hpp"
#include "TestScene.hpp"

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
	static const GLfloat vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f,
	};
}

namespace Scenes
{
	TestScene::TestScene()
	{
	}

	void TestScene::initialize()
	{
		ResourceTypes::Shader fragment{ ResourceTypes::ShaderType::Fragment, default_fragment_shader };
		ResourceTypes::Shader vertex{ ResourceTypes::ShaderType::Vertex, default_vertex_shader };

		program.attachShader(vertex);
		program.attachShader(fragment);
		program.linkProgram();
		program.detachShader(fragment);
		program.detachShader(vertex);

		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
	}

	void TestScene::onRender(double elapsed)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		program.useProgram();

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDisableVertexAttribArray(0);
	}
}
