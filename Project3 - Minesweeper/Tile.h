#pragma once
#include "TextureManager.h"

class Tile
{
	sf::Sprite hiddenTile_;
	sf::Sprite revealedTile_;
	bool isHidden_ = true;
	int xPos = 0;
	int yPos = 0;

public:
	Tile();
	sf::Sprite drawTile(const sf::Vector2f& position);
};

