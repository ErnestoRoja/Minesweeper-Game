#include "TextureManager.h"

// redeclare the variable, so this file knows it exists and can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string fileName)
{
	string path = "images/";
	path += fileName + ".png";

	textures[fileName].loadFromFile(path);
}

sf::Texture& GetTexture(string textureName)
{

}