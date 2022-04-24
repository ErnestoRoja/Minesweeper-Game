#pragma once
#include "Random.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	// static == one and only one of these in memory, ever
	static unordered_map<string, sf::Texture> textures;
	static void LoadTexture(string textureName);
	// static string imagesDirectory;  -->  (later use in other projects)
public:
	static sf::Texture& GetTexture(string textureName);
	static void Clear(); // Call this once, at the end of main
	// static void SetImagesDirectory(string directoryPath);  -->  (later use in other projects)
};

