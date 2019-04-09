#pragma once

#include <glad/glad.h>
#include <HearthLib/FileBundle.hpp>

#include "../Core/Scene.hpp"
#include "../ResourceTypes/ShaderProgram.hpp"

namespace Scenes
{
	class TestScene : public ::Core::Scene
	{
	public:
		TestScene();

		void initialize();

		void onRender(double lag);

	private:
		ResourceTypes::ShaderProgram program;
		GLuint vertex_array_id;
		GLuint vertex_buffer;
		GLuint uv_buffer;
		GLuint texture_id;

		HearthLib::FileBundle assets{ "shaders.bundle" };
	};
}
