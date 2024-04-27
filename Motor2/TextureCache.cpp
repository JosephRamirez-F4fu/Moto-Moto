#include "TextureCache.h"
#include "ImageLoader.h"
TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath)
{
	auto it =
		textureMap.find(texturePath);
	if (it == textureMap.end())
	{
		GLTexture newTexture = ImageLoader::loadPNG(texturePath);
		pair<string, GLTexture> newPair(texturePath, newTexture);
		textureMap.insert( newPair);
		return newTexture;
	}
	return it->second;
}
