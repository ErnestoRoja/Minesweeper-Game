#include "Tile.h"

Tile::Tile()
{
	isHidden_ = true;
}

sf::Sprite Tile::drawTile(const sf::Vector2f& position)
{
	sf::Sprite hidden(TextureManager::GetTexture("tile_hidden"));
	hidden.setPosition(position);

	if (!isHidden_)
	{
		sf::Sprite revealed(TextureManager::GetTexture("tile_revealed"));
		revealed.setPosition(position);
		revealed.move(3.5f, -3.5f);
		return revealed;
	}

	return hidden;
}
