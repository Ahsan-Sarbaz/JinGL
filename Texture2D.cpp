#include "Texture2D.h"

#include <stb_image.h>
#include "GL.h"

Texture2D::Texture2D()
	:id(0), width(0), height(0), format(Format::Unknown)
{ }

Texture2D::Texture2D(const char* path, bool flip)
	:id(0), format(Format::Unknown)
{
	stbi_set_flip_vertically_on_load(flip);
	int channels = 0;
	auto data = stbi_load(path, &width, &height, &channels, 0);
	if (data == nullptr)
		return;

	switch (channels)
	{
	case 1: format = Format::R8; break;
	case 2: format = Format::RG8; break;
	case 3: format = Format::RGB8; break;
	case 4: format = Format::RGBA8; break;
	}

	FromData(width, height, format, data);
	stbi_image_free(data);
}

Texture2D::Texture2D(int width, int height, Format format, unsigned char* data)
{
	FromData(width, height, format, data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &id);
}

void Texture2D::GenerateMipmaps()
{
	glGenerateTextureMipmap(id);
}

void Texture2D::Bind(int unit)
{
	glBindTextureUnit(unit, id);
}

void Texture2D::FromData(int width, int height, Format format, unsigned char* data)
{
	this->width = width;
	this->height = height;
	this->format = format;

	glCreateTextures(GL_TEXTURE_2D, 1, &id);
	glTextureStorage2D(id, 1, GLenum(format), width, height);

	if (data != nullptr)
	{
		GLenum pixelFormat = 0;
		switch (format)
		{
		case Format::R8: pixelFormat = GL_RED; break;
		case Format::RG8: pixelFormat = GL_RG; break;
		case Format::RGB8: pixelFormat = GL_RGB; break;
		case Format::RGBA8: pixelFormat = GL_RGBA; break;
		}

		glTextureSubImage2D(id, 0, 0, 0, width, height, pixelFormat, GL_UNSIGNED_BYTE, data);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);
		float aniso = 0.0f;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &aniso);
		glTextureParameterf(id, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
	}

}

