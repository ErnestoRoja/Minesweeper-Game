#pragma once
#include <unordered_map>
#include "Tile.h"
using namespace std;

class Board : private Tile
{
	unsigned int ROWS = 0;
	unsigned int COLUMNS = 0;
	vector<vector<Tile>> board;

public:
	Board();
	Board(unsigned int columns, unsigned int rows);
	void drawBoard();
	
};