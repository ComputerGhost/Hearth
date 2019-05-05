#pragma once

#include <glad/glad.h>
#include <Engine/Formats/Bundle.hpp>
#include <Engine/State.hpp>

#include "../ResourceTypes/ShaderProgram.hpp"

namespace Scenes
{
	class TestScene : public Hearth::State
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

		Hearth::Formats::Bundle assets{ "shaders.bundle" };
	};
}
