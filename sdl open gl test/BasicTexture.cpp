#include "BasicTexture.h"

Texture::BasicTexture::~BasicTexture()
{
	free(surface);
}

void Texture::BasicTexture::load(const std::string & fileName)
{
	std::string filePath = fileName + ".png";

	surface = IMG_Load(filePath.c_str());

	glGenTextures(1, &m_textureId);
	glBindTexture(GL_TEXTURE_2D, m_textureId);

	int mode = GL_RGB;

	if (surface == nullptr) {
		printf("didnt load surface");
	}
	if (surface->format->BytesPerPixel == 4) {
		mode = GL_RGBA;
	}

	glTexImage2D(GL_TEXTURE_2D,
		0,
		mode,
		surface->w,
		surface->h,
		0,
		mode,
		GL_UNSIGNED_BYTE,
		surface->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	//free(surface);
}

void Texture::BasicTexture::bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}

void Texture::BasicTexture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
