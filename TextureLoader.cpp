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

	for (const auto& p : instance->promises)
	{
		const auto& [_path, _flip, _index] = p;
		if (path == _path && flip == _flip)
		{
			printf("Re-Using Texture %s\n", path.c_str());
			return instance->textures[_index];
		}
	}

	instance->promises.push_back({ path , flip, instance->index++});
	instance->textures.push_back(new Texture2D);
	return instance->textures.back();
}

struct PromisedTexture
{
	std::string path;
	unsigned char* data;
	int data_size;
	int width, height, channels;
};

void TextureLoader::LoadPromisedTextures()
{
	if (instance == nullptr)
	{
		instance = new TextureLoader;
		return;
	}

	if (promises.empty()) return;

	auto promisedTextures = new PromisedTexture[promises.size()];
	memset(promisedTextures, 0, sizeof(PromisedTexture) * promises.size());

	for (size_t i = 0; i < promises.size(); i++)
	{
		const auto& [path, flip, index] = promises[i];

		FILE* file;
		fopen_s(&file, path.c_str(), "rb");
		if (file) {
			fseek(file, 0, SEEK_END);
			auto size = ftell(file);
			rewind(file);
			auto buffer = new unsigned char[size];
			if (buffer) {
				fread_s(buffer, size, 1, size, file);
				promisedTextures[i].data = buffer;
				promisedTextures[i].data_size = int(size);
			}
		}
	}

	std::for_each(std::execution::par_unseq, promises.begin(), promises.end(),
		[&](std::tuple<std::string, bool, int>& promise) {
			const auto& [path, flip, index] = promise;
			auto& p = promisedTextures[index];
			if (p.data != nullptr)
			{
				stbi_set_flip_vertically_on_load(flip);
				auto buffer = stbi_load_from_memory(p.data, p.data_size, &p.width, &p.height, &p.channels, 0);
				delete[] p.data;
				p.data = buffer;
				p.data_size = -1;
			}
		});

	for (int i = 0; i < promises.size(); i++)
	{
		auto& p = promisedTextures[i];
		if (p.data != nullptr)
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
			textures[i]->GenerateMipmaps();
			stbi_image_free(p.data);
		}
	}

	delete[] promisedTextures;

	index = 0;
	promises.clear();
	textures.clear();
}
