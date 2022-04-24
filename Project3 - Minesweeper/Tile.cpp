#include "Tile.h"

// Default constructor for a tile.
Tile::Tile()
{
	hasMine_ = false;
	hasFlag_ = false;
	isLeftClicked_ = false;
	isRightClicked_ = false;
	isRevealed_ = false;
	endOfGame = false;
	tileDebug_ = false;
}

// Sets the pixel locations of a tile, based on its coordinates.
void Tile::setTilePosition(float x_cord, float y_cord)
{
	x = x_cord * 32;
	y = y_cord * 32;
}

// Adjusts a tile's sprite depending on how you interact with it.
void Tile::setTileSprite()
{
	if (isLeftClicked_ == false && isRightClicked_ == false && endOfGame == false)
	{
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
	}
	else if (hasFlag_ == true && isRevealed_ == false && endOfGame == false)
	{
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
		hasFlag_ = false;
		if (hasMine_ == true && tileDebug_ == false)
		{
			mineSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
		}
	}
	else if (isLeftClicked_ == false && isRightClicked_ == true && isRevealed_ == false && hasFlag_ == false && endOfGame == false)
	{
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
		hasFlag_ = true;
		if (hasMine_ == true && tileDebug_ == false)
		{
			mineSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
		}
	}
	else if (isLeftClicked_ == true && hasMine_ == false && hasFlag_ == false && endOfGame == false)
	{
		if (surroundingMines == 1)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_1"));
		}
		else if (surroundingMines == 2)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_2"));
		}
		else if (surroundingMines == 3)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_3"));
		}
		else if (surroundingMines == 4)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_4"));
		}
		else if (surroundingMines == 5)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_5"));
		}
		else if (surroundingMines == 6)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_6"));
		}
		else if (surroundingMines == 7)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_7"));
		}
		else if (surroundingMines == 8)
		{
			numberSprite_ = sf::Sprite(TextureManager::GetTexture("number_8"));
		}
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
		isRevealed_ = true;
	}
	else if (isLeftClicked_ == true && hasMine_ == true && hasFlag_ == true && isRevealed_ == true)
	{
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
	}
	else if (isLeftClicked_ == true && hasMine_ == true && endOfGame == false && hasFlag_ == false)
	{
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
	}
	tileSprite_.setPosition(x, y);
	flagSprite_.setPosition(x, y);
	mineSprite_.setPosition(x, y);
	numberSprite_.setPosition(x, y);
}

sf::Sprite Tile::getTileSprite()
{
	return tileSprite_;
}

sf::Sprite Tile::getMineSprite()
{
	return mineSprite_;
}

sf::Sprite Tile::getFlagSprite()
{
	return flagSprite_;
}

sf::Sprite Tile::getNumberSprite()
{
	return numberSprite_;
}

// Sets the number of surrounding mines to a tile.
void Tile::setNumSurroundingMines(int numMines)
{
	this->surroundingMines = numMines;
}

// Used to not allow further interactions with a tile. 
void Tile::setEndOfGame(Tile& targetTile)
{
	targetTile.endOfGame = true;
}

// Recursively checks if the neighbors of a tile have not been left clicked, don't have a flag, and do not have a mine, if so, reveal that tile.
void Tile::revealTile(Tile& targetTile)
{
	targetTile.isLeftClicked_ = true;
	targetTile.isRevealed_ = true;
	revealedTileCounter++;
		
	if (targetTile.hasMine_ == false && targetTile.surroundingMines == 0)
	{
		for (int i = 0; i < targetTile.adjacentTiles.size(); i++)
		{
			if (targetTile.adjacentTiles[i]->isLeftClicked_ == false && targetTile.adjacentTiles[i]->hasFlag_ == false && targetTile.adjacentTiles[i]->hasMine_ == false)
			{
				revealTile(*targetTile.adjacentTiles[i]);
			}
		}
	}
	targetTile.setTileSprite();
}

// Sets a tile as being right clicked and adjusts its sprites to add a flag.
void Tile::flagTile(Tile& targetTile)
{
	targetTile.isRightClicked_ = true;
	
	targetTile.setTileSprite();
}

// Updates the mine sprite (to show).
void Tile::showMines()
{
	mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
	mineSprite_.setPosition(x, y);
}

// Updates the mine sprite (to hide).
void Tile::hideMines()
{
	if (hasFlag_ == true)
	{
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
	}
	else
	{
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
	}
	mineSprite_.setPosition(x, y);
	tileSprite_.setPosition(x, y);
	flagSprite_.setPosition(x, y);
}

// Reveals all the mines when the game is over.
void Tile::allMineReveal(Tile& targetTile)
{
	targetTile.isRevealed_ = true;

	if (targetTile.hasFlag_ == false)
	{
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));
	}
	mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
	tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_revealed"));

	mineSprite_.setPosition(x, y);
	flagSprite_.setPosition(x, y);
	tileSprite_.setPosition(x, y);
}

// Flags all the mines when the game is over.
void Tile::flagAllMines(Tile& targetTile)
{
	targetTile.hasFlag_ = true;

	if (targetTile.tileDebug_ == true)
	{
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("mine"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
	}
	else
	{
		tileSprite_ = sf::Sprite(TextureManager::GetTexture("tile_hidden"));
		mineSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
		flagSprite_ = sf::Sprite(TextureManager::GetTexture("flag"));
	}
	
	tileSprite_.setPosition(x, y);
	mineSprite_.setPosition(x, y);
	flagSprite_.setPosition(x, y);
}