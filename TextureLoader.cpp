#include "TextureLoader.h"
#include <execution>
#include <stb_image.h>

TextureLoader* TextureLoader::instance = nullptr;

Texture2D* TextureLoader::Load(const std::string& path, bool flip)
{
	if (instance == nullptr)
	{
		instance = new TextureLoader;
	}

	instance->promises.push_back({ path , flip, instance->index++});
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
	auto promisedTextures = new PromisedTexture[promises.size()];

	std::for_each(std::execution::par_unseq, promises.begin(), promises.end(),
		[&](std::tuple<std::string, bool, int>& promise) {
			const auto& [path, flip, index] = promise;
			PromisedTexture p;
			stbi_set_flip_vertically_on_load(flip);
			p.data = (unsigned char*)stbi_load(path.c_str(), &p.width, &p.height, &p.channels, 0);
			promisedTextures[index] = p;
		});

	for (int i = 0; i < promises.size(); i++)
	{
		auto& p = promisedTextures[i];

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

	delete[] promisedTextures;

	index = 0;
	promises.clear();
}
