#pragma once
#include "Texture2D.h"
#include <string>
#include <vector>
#include <tuple>

class TextureLoader
{
public:
	/**
	* gets the static instance of TextureLoader since its a singleton
	* @returns TextureLoader*
	*/
	static TextureLoader* Get() { return instance; }

	/**
	* promises the load a texture at another time ( by calling LoadPromisedTextures)
	* @param path path to the texture file (relative to the .exe)
	* @param flip flip the texture vertically
	*/
	static Texture2D* Load(const std::string& path, bool flip = false);

	/**
	* actually loads all the textures that were promised to this point. the loading is done on multiple threads
	* but the texture creation and data copy is done on the main thread since OpenGL is single threaded
	*/
	void LoadPromisedTextures();

private:
	static TextureLoader* instance;

	std::vector<std::tuple<std::string, bool>> promises;
	std::vector<Texture2D*> textures;
};

