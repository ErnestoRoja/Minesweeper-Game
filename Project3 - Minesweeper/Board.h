#pragma once
#include <unordered_map>
#include "Button.h"

using namespace std;

class Board : private Tile, private Button
{
	unsigned int ROWS;
	unsigned int COLUMNS;
	int MINES;
	int totalTiles;
	int mineCounter;
	int flagCounter;
	
	int tilesToWin;
	bool endOfGame = false;
	
	sf::Sprite onesDigits;
	sf::Sprite tensDigits;
	sf::Sprite hundredsDigits;
	sf::Sprite negativeDigits;

public:
	bool debugMode = false;
	bool gameOver = false;
	bool test1 = false;
	bool test2 = false;
	bool test3 = false;

	Board(unsigned int columns, unsigned int rows, int mines);
	vector<vector<Tile>> board;

	void setBoardSprites(vector<vector<Tile>>& targetTile);
	void storeNeighbors();

	void surroundingMines(vector<vector<Tile>>& targetTile);
	void setMines(vector<vector<Tile>>& targetTile, int numMines);
	void setBoardMineCount(int testMines);
	void showAllMines();
	void hideAllMines();
	
	void revealBoardTile(float x_cord, float y_cord);
	void flagTile(float x_cord, float y_cord);
	void gameOverMines();
	void gameOverFlags();

	Board restartBoard();
	void checkGameLose(sf::RenderWindow& window);
	void checkGameWin(sf::RenderWindow& window);
	void testBoards(Board& testBoard, string filename);
	void resetCounts(int newTileCount, int newMineCount);

	void clickButtons(float x_cord, float y_cord);
	void drawButtons(sf::RenderWindow& window);
	void drawDigits(sf::RenderWindow& window);
	void changeDigits(int ones, int tens, int hundreds);
};