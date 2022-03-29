#include "Tile.h"

Tile::Tile()
{
	isHidden_ = true;
}

sf::Sprite Tile::drawTile()
{
	sf::Sprite hidden(TextureManager::GetTexture("tile_hidden"));

	if (!isHidden_)
	{
		sf::Sprite revealed(TextureManager::GetTexture("tile_revealed"));
		return revealed;
	}

	return hidden;
}
