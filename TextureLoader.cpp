#include "TextureLoader.h"
#include <execution>
#include <stb_image.h>

TextureLoader* TextureLoader::instance = nullptr;

Texture2D* TextureLoader::Load(const std::string& path)
{
	if (instance == nullptr)
	{
		instance = new TextureLoader;
	}

	instance->promises.push_back(path);
	instance->textures.push_back(new Texture2D);
	return instance->textures.back();
}

struct PromisedTexture
{
	std::string path;
	unsigned char* data;
	int width, height, channels;
};

void TextureLoader::LoadPromisedTextures()
{
	std::vector<PromisedTexture> promisedTextures;

	stbi_set_flip_vertically_on_load(true);
	std::for_each(std::execution::par_unseq, promises.begin(), promises.end(),
		[&](const std::string& path) {
			PromisedTexture p;
			p.data = (unsigned char*)stbi_load(path.c_str(), &p.width, &p.height, &p.channels, 0);
			promisedTextures.push_back(p);
		});

	int i = 0;
	for (const auto& p : promisedTextures)
	{
		Format format = Format::Unknown;
		switch (p.channels)
		{
		case 1: format = Format::R8; break;
		case 2: format = Format::RG8; break;
		case 3: format = Format::RGB8; break;
		case 4: format = Format::RGBA8; break;
		}
		textures[i]->FromData(p.width, p.height, format, p.data);
	}

	promises.clear();
}
