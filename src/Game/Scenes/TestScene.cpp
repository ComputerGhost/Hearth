#include "../ResourceTypes/Shader.hpp"
#include "TestScene.hpp"

namespace
{
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
		int length = static_cast<int>(assets.open("test.frag"));
		std::unique_ptr<char[]> code{ new char[length + 1] };
		assets.getStream().read(code.get(), length);
		code.get()[length] = '\0';
		ResourceTypes::Shader fragment{ ResourceTypes::ShaderType::Fragment, code.get() };

		length = static_cast<int>(assets.open("test.vert"));
		code.reset(new char[length + 1]);
		assets.getStream().read(code.get(), length);
		code.get()[length] = '\0';
		ResourceTypes::Shader vertex{ ResourceTypes::ShaderType::Vertex, code.get() };

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
