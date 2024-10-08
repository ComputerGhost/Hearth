#include <glm/gtc/matrix_transform.hpp>
#include <Engine/Formats/Binary.hpp>
#include <Engine/Window.hpp>
#include "../ResourceTypes/Shader.hpp"
#include "TestScene.hpp"

namespace
{
	static const GLfloat g_vertex_buffer_data[] = {
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		 1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		 1.0f,-1.0f,-1.0f,
	};
	static const GLfloat g_uv_buffer_data[] = {
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 1.0f,
	0.0f, 0.0f,
	1.0f, 0.0f,
	};

	GLuint loadBitmap(const char *filename)
	{
		std::ifstream in(filename, std::ios_base::binary);
		if (!in.is_open())
			throw std::runtime_error("file not found.");

		in.ignore(18);
		std::uint32_t width = Hearth::Formats::Binary::readDWord(in);
		width = ((width & 0xff) << 24) + (((width >> 8) & 0xff) << 16) + (((width >> 16)&0xff) << 8) + ((width >> 24) & 0xff);
		std::uint32_t height = Hearth::Formats::Binary::readDWord(in);
		height = ((height & 0xff) << 24) + (((height >> 8) & 0xff) << 16) + (((height >> 16)&0xff) << 8) + ((height >> 24) & 0xff);
		in.ignore(4);

		auto buffer = std::make_unique<char[]>(width*height*3);
		in.read(buffer.get(), width*height*3);

		GLuint texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, buffer.get());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		return texture_id;
	}
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

		texture_id = loadBitmap("test.bundle/splash.bmp");
		if (texture_id == 0)
			throw std::runtime_error("Unable to load texture.");

		program.attachShader(vertex);
		program.attachShader(fragment);
		program.linkProgram();
		program.detachShader(fragment);
		program.detachShader(vertex);

		glGenVertexArrays(1, &vertex_array_id);
		glBindVertexArray(vertex_array_id);

		glGenBuffers(1, &vertex_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

		glGenBuffers(1, &uv_buffer);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
	}

	void TestScene::onRender(double lag)
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		program.useProgram();

		auto size = Hearth::window->getFramebufferSize();
		float aspect = static_cast<float>(size.x) / size.y;
		glViewport(0, 0, size.x, size.y);
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspect, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(
			glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 mvp = projection * view * model;

		GLuint matrixId = program.getUniformLocation("MVP");
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, &mvp[0][0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glUniform1i(texture_id, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uv_buffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, 2*3);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
}
