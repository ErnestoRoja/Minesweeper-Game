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

void Board::drawBoard()
{
	
	for (unsigned int i = 0; i <= COLUMNS; i++)
	{
		vector<Tile> temp;
		for (unsigned int j = 0; j < ROWS; j++)
		{
			board.push_back(temp);
		}
	}


	for (unsigned int i = 0; i < board.size(); i++)
	{
		for (unsigned int j = 0; j < board[i].size(); j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
}

