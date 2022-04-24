#pragma once
#include "TextureManager.h"

class Tile
{
public:
	sf::Sprite tileSprite_;
	sf::Sprite mineSprite_;
	sf::Sprite numberSprite_;
	sf::Sprite flagSprite_;

	unsigned int revealedTileCounter = 0;
	bool isLeftClicked_;
	bool isRightClicked_;
	bool hasMine_;
	int surroundingMines;
	bool hasFlag_;
	bool isRevealed_;
	bool tileDebug_;
	float x;
	float y;

	bool endOfGame;

	Tile();
	std::vector<Tile*> adjacentTiles;
	void setTilePosition(float x_cord, float y_cord);
	void setTileSprite();
	sf::Sprite getTileSprite();
	sf::Sprite getMineSprite();
	sf::Sprite getFlagSprite();
	sf::Sprite getNumberSprite();
	
	void setNumSurroundingMines(int numMines);
	void setEndOfGame(Tile& targetTile);

	void revealTile(Tile& targetTile);
	void flagTile(Tile& targetTile);
	
	void showMines();
	void hideMines();
	void allMineReveal(Tile& targetTile);
	void flagAllMines(Tile& targetTile);
};