#pragma once
#include"GLTexture.h"
#include"TextureCache.h"
using namespace std;
class ResourceManager
{
public:
	static GLTexture getTexture(std::string texturePath);
private:
	static TextureCache textureCache;
};