#pragma once
#include "TextureManager.h"

class Tile
{
	sf::Sprite hiddenTile_;
	sf::Sprite revealedTile_;
	bool isHidden_ = true;

public:
	Tile();
	sf::Sprite drawTile();
};

