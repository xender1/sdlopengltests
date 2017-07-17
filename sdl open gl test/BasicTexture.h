#pragma once

#include <GL/glew.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <memory>

namespace Texture
{
	
	class BasicTexture
	{
	public:
		~BasicTexture();

		void load(const std::string& fileName);

		void bind();
		void unbind();

	private:
		GLuint m_textureId;

		SDL_Surface* surface;

	};
}