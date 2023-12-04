#pragma once

enum class Format
{
	Unknown = 0, 
	R32I = 0x8235,
	R32UI = 0x8236,
	R8 = 0x8229,
	RG8 = 0x822B,
	RGB8 = 0x8051,
	RGBA8 = 0x8058,
	RGBA16F = 0x881A,
	D24S8 = 0x88F0
};

class Texture2D
{
friend class TextureLoader;

public:
	Texture2D();

	/**
	* creates a texture from file path
	* @param path path to the file 
	* @param flip true to flip texture vertically on load else false
	*/
	explicit Texture2D(const char* path, bool flip);

	/**
	* creates a texture from data
	* @param width width of the texture
	* @param height height of the texture
	* @param format pixel format of the texture
	* @param data pointer to texture data (if null only the storage is allocated)
	*/
	explicit Texture2D(int width, int height, Format format, unsigned char* data = nullptr);

	/**
	* deletes the underlying OpenGL handle
	*/
	~Texture2D();

	/**
	* generate the mip maps
	*/
	void GenerateMipmaps();
	
	/**
	* binds the texture to the specified unit
	* @param unit texture unit to bind to
	*/
	void Bind(int unit);

	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetID() const { return id; }
	
	/**
	* gets width of the texture
	* @returns width
	*/
	int GetWidth() const { return width; }

	/**
	* gets height of the texture
	* @returns height
	*/
	int GetHeight() const { return height; }
	
	/**
	* gets format of the texture
	* @returns format
	*/
	Format GetFormat() const { return format; }

private:
	/**
	* creates a texture from data
	* @param width width of the texture
	* @param height height of the texture
	* @param format pixel format of the texture
	* @param data pointer to texture data (if null only the storage is allocated)
	*/
	void FromData(int width, int height, Format format, unsigned char* data);

	unsigned int id;
	int width, height;
	Format format;
};