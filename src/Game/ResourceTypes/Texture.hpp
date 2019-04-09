#pragma once

#include <glad/glad.h>

#include "TextureType.hpp"

namespace ResourceTypes
{
	class Texture
	{
	public:
		Texture() = delete;
		Texture(const Texture &) = delete;
		explicit Texture(TextureType type, const char *source);
		~Texture();

		void bind();

	private:
		GLuint id;
	};
}
