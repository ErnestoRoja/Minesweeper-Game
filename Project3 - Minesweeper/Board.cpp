#include "Board.h"
#include <iostream>

Board::Board()
{
	unsigned int ROWS = 0;
	unsigned int COLUMNS = 0;
	vector<vector<Tile>> board;
}

Board::Board(unsigned int columns, unsigned int rows)
{
	COLUMNS = columns;
	ROWS = rows;
}

void Board::drawBoard(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < COLUMNS; i++)
	{
		for (unsigned int j = 0; j < ROWS; j++)
		{
			sf::Vector2f position(1.2f * COLUMNS * i, 2.0f * ROWS * j);
			sf::Sprite tile = drawTile(position);
			window.draw(tile);
		}
	}
}
