#include "Board.h"
#include <iostream>
#include <fstream>

// Creates a board.
Board::Board(unsigned int columns, unsigned int rows, int mines)
{
	this->COLUMNS = columns;
	this->ROWS = rows;
	this->MINES = mines;
	flagCounter = mines;

	totalTiles = COLUMNS * ROWS;
	tilesToWin = totalTiles - MINES;

	// Creates the board, which is made up of tiles (# of tiles = COLUMNS * ROWS).
	for (unsigned int i = 0; i < ROWS; i++)
	{
		board.push_back(vector<Tile>());
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			board[i].push_back(Tile());
		}
	}
	storeNeighbors();
	setBoardSprites(board);
	setMines(board, MINES);
	surroundingMines(board);
}

// Sets the board sprites.
void Board::setBoardSprites(vector<vector<Tile>>& targetTile)
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			board[i][j].setTilePosition(j, i);
			board[i][j].setTileSprite();
		}
	}
}

// Each tile's neighbor is stored, which helps in determining whether nearby tiles should be revealed recursively or not.
void Board::storeNeighbors()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			// The neighbors of the top leftmost tile.
			if (i == 0 && j == 0)
			{
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
			}
			// The neighbors of the top rightmost tile.
			else if (i == 0 && j == COLUMNS - 1)
			{
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
			}
			// The neighbors of the bottom leftmost tile.
			else if (i == ROWS - 1 && j == 0)
			{
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
			}
			// The neighbors of the bottom rightmost tile.
			else if (i == ROWS - 1 && j == COLUMNS - 1)
			{
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
			}
			// The neighbors of the tiles on the top.
			else if (i == 0)
			{
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j + 1]);
			}
			// The neighbors of the tiles on the left.
			else if (j == 0)
			{
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
			}
			// The neighbors of the tiles on the bottom.
			else if (i == ROWS - 1)
			{
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j + 1]);
			}
			// The neighbors of the tiles on the right.
			else if (j == COLUMNS - 1)
			{
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
			}
			// The neighbors of tiles not on the edge of the board.
			else
			{
				board[i][j].adjacentTiles.push_back(&board[i - 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i - 1][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i][j + 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j - 1]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j]);
				board[i][j].adjacentTiles.push_back(&board[i + 1][j + 1]);
			}
		}
	}
}

// Calculates the number of mines surrounding a tile by checking if there is a mine in each neighboring tile.
void Board::surroundingMines(vector<vector<Tile>>& targetTile)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true)
			{
				continue;
			}

			int mineCounter = 0;

			// Top left corner
			if (i - 1 >= 0 && j - 1 >= 0)
			{
				if (board[i - 1][j - 1].hasMine_ == true)
					mineCounter++;
			}
			// Top 
			if (i - 1 >= 0) {

				if (board[i - 1][j].hasMine_ == true)
					mineCounter++;

			}
			// Top right corner
			if (i - 1 >= 0 && j + 1 < COLUMNS)
			{
				if (board[i - 1][j + 1].hasMine_ == true)
					mineCounter++;
			}
			// Right
			if (j + 1 < COLUMNS)
			{
				if (board[i][j + 1].hasMine_ == true)
					mineCounter++;
			}
			// Bottom right corner
			if (i + 1 < ROWS && j + 1 < COLUMNS)
			{
				if (board[i + 1][j + 1].hasMine_ == true)
					mineCounter++;
			}
			// Bottom
			if (i + 1 < ROWS)
			{
				if (board[i + 1][j].hasMine_ == true)
					mineCounter++;

			}
			// Bottom Left corner
			if (i + 1 < ROWS && j - 1 >= 0)
			{
				if (board[i + 1][j - 1].hasMine_ == true)
					mineCounter++;
			}
			// Left
			if (j - 1 >= 0)
			{
				if (board[i][j - 1].hasMine_ == true)
					mineCounter++;
			}
			board[i][j].setNumSurroundingMines(mineCounter);
		}
	}
}

// Based on the number of mines, this will determine which tiles contain a mine, randomly.
void Board::setMines(vector<vector<Tile>>& targetTile, int numMines)
{
	int r_Index = 0;
	int c_Index = 0;
	for (unsigned int i = 0; i < numMines; i++)
	{
		r_Index = Random::Int(0, ROWS - 1);
		c_Index = Random::Int(0, COLUMNS - 1);

		if (targetTile[r_Index][c_Index].hasMine_ == true)
		{
			i--;
		}
		else
		{
			targetTile[r_Index][c_Index].hasMine_ = true;
			mineCounter++;
		}
	}
}

// Sets the mine count of the board (used for loading test boards).
void Board::setBoardMineCount(int testMines)
{
	this->MINES = testMines;
}

// Shows all the mines on the board.
void Board::showAllMines()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true)
			{
				board[i][j].showMines();
				board[i][j].tileDebug_ = true;
			}
		}
	}
}

// Hides all the mines.
void Board::hideAllMines()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true)
			{
				board[i][j].hideMines();
				board[i][j].tileDebug_ = false;
			}
		}
	}
}

// Reveals a tile depending on the position of the mouse when clicked (does not reveal if tile has been flagged).
void Board::revealBoardTile(float x_cord, float y_cord)
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if ((board[i][j].x <= x_cord) && (x_cord < board[i][j].x + 32) && (board[i][j].y <= y_cord) && (y_cord < board[i][j].y + 32) && (board[i][j].hasFlag_ == false) && (board[i][j].isRevealed_ == false))
			{
				board[i][j].revealTile(board[i][j]);
				tilesToWin -= board[i][j].revealedTileCounter;
			}
		}
	}
}

// Flags a tile depending on the position of the mouse when clicked.
void Board::flagTile(float x_cord, float y_cord)
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if ((board[i][j].x <= x_cord) && (x_cord < board[i][j].x + 32) && (board[i][j].y <= y_cord) && (y_cord < board[i][j].y + 32) && (board[i][j].hasFlag_ == false) && (board[i][j].isRevealed_ == false) && (board[i][j].endOfGame == false))
			{
				board[i][j].flagTile(board[i][j]);
				flagCounter--;
			}
			else if ((board[i][j].x <= x_cord) && (x_cord < board[i][j].x + 32) && (board[i][j].y <= y_cord) && (y_cord < board[i][j].y + 32) && (board[i][j].hasFlag_ == true) && (board[i][j].endOfGame == false))
			{
				board[i][j].flagTile(board[i][j]);
				flagCounter++;
			}
		}
	}
}

// Reveals all mines when the game is over.
void Board::gameOverMines()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true && endOfGame == true)
			{
				board[i][j].allMineReveal(board[i][j]);
			}
		}
	}
}

// Flags all the mines when the game is over.
void Board::gameOverFlags()
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true && board[i][j].hasFlag_ == false && endOfGame == true)
			{
				board[i][j].flagAllMines(board[i][j]);
			}
		}
	}
}

// Creates a new board.
Board Board::restartBoard()
{
	int newColumns = COLUMNS;
	int newRows = ROWS;
	int newMines = MINES;

	Board newBoard = Board(newColumns, newRows, newMines);

	return newBoard;
}

// Checks the losing conditions of the game.
void Board::checkGameLose(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].hasMine_ == true && board[i][j].isLeftClicked_ == true)
			{
				endOfGame = true;
				int windowHeight = (ROWS * 32) + 100;
				sf::Vector2f facePosition((window.getSize().x / 2) - 32, (windowHeight - 100));
				sf::Sprite faceButton = drawSadFaceButton(facePosition);
				window.draw(faceButton);
				gameOverMines();
			}
			if (endOfGame == true)
			{
				board[i][j].setEndOfGame(board[i][j]);
			}
		}
	}
}

// Checks the winning conditions of the game.
void Board::checkGameWin(sf::RenderWindow& window)
{
	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (board[i][j].isRightClicked_ == true && board[i][j].hasMine_ == true && flagCounter == 0 && tilesToWin == 0)
			{
				endOfGame = true;
				int windowHeight = (ROWS * 32) + 100;
				sf::Vector2f facePosition((window.getSize().x / 2) - 32, (windowHeight - 100));
				sf::Sprite faceButton = drawWinnerFaceButton(facePosition);
				window.draw(faceButton);
				gameOverFlags();
			} 
			else if (tilesToWin == 0)
			{
				endOfGame = true;
				int windowHeight = (ROWS * 32) + 100;
				sf::Vector2f facePosition((window.getSize().x / 2) - 32, (windowHeight - 100));
				sf::Sprite faceButton = drawWinnerFaceButton(facePosition);
				window.draw(faceButton);
				gameOverFlags();
			}
			if (endOfGame == true)
			{
				board[i][j].setEndOfGame(board[i][j]);
			}
		}
	}
}

// Reads the test board files and creates a new board depending on the binary map of the file.
void Board::testBoards(Board& testBoard, string filename)
{
	vector<int> testFileData;
	ifstream file(filename);
	char tempNumber;
	int index = 0;
	int newTileCount = 0;
	int newMineCount = 0;

	while (!file.eof())
	{
		file >> tempNumber;
		testFileData.push_back(tempNumber);
	}

	for (unsigned int i = 0; i < testFileData.size() - 1; i++)
	{
		if (testFileData.at(i) == 49)
		{
			newMineCount++;
		}
		else if (testFileData.at(i) == 48)
		{
			newTileCount++;
		}
	}

	for (unsigned int i = 0; i < ROWS; i++)
	{
		for (unsigned int j = 0; j < COLUMNS; j++)
		{
			if (testFileData.at(index) == 49)
			{
				board[i][j].hasMine_ = true;
				mineCounter++;
			}
			else
			{
				board[i][j].hasMine_ = false;
			}
			index++;
		}
	}
	setBoardMineCount(newMineCount);
	surroundingMines(board);
	resetCounts(newTileCount, newMineCount);
}

// Resets the flag counter based on the number of mines on the board (which resets the digits), along with the number of tiles left to open. 
void Board::resetCounts(int newTileCount, int newMineCount)
{
	this->tilesToWin = newTileCount;
	this->flagCounter = newMineCount;
}

// Determines what each button does when clicked.
void Board::clickButtons(float x_cord, float y_cord)
{
	if ((allButtons["smileyFaceButton"].getPosition().x <= x_cord) && (x_cord < allButtons["smileyFaceButton"].getPosition().x + 64) && (allButtons["smileyFaceButton"].getPosition().y <= y_cord) && (y_cord < allButtons["smileyFaceButton"].getPosition().y + 64) && debugMode == false)
	{
		hideAllMines();
		gameOver = true;
	}
	else if ((allButtons["smileyFaceButton"].getPosition().x <= x_cord) && (x_cord < allButtons["smileyFaceButton"].getPosition().x + 64) && (allButtons["smileyFaceButton"].getPosition().y <= y_cord) && (y_cord < allButtons["smileyFaceButton"].getPosition().y + 64))
	{
		gameOver = true;
		showAllMines();
		debugMode = true;
	}
	if ((allButtons["debugButton"].getPosition().x <= x_cord) && (x_cord < allButtons["debugButton"].getPosition().x + 64) && (allButtons["debugButton"].getPosition().y <= y_cord) && (y_cord < allButtons["debugButton"].getPosition().y + 64) && endOfGame == true)
	{
		return;
	}
	else if ((allButtons["debugButton"].getPosition().x <= x_cord) && (x_cord < allButtons["debugButton"].getPosition().x + 64) && (allButtons["debugButton"].getPosition().y <= y_cord) && (y_cord < allButtons["debugButton"].getPosition().y + 64) && debugMode == true)
	{
		hideAllMines();
		debugMode = false;
		return;
	}
	else if ((allButtons["debugButton"].getPosition().x <= x_cord) && (x_cord < allButtons["debugButton"].getPosition().x + 64) && (allButtons["debugButton"].getPosition().y <= y_cord) && (y_cord < allButtons["debugButton"].getPosition().y + 64))
	{
		showAllMines();
		debugMode = true;
	}
	if ((allButtons["test1Button"].getPosition().x <= x_cord) && (x_cord < allButtons["test1Button"].getPosition().x + 64) && (allButtons["test1Button"].getPosition().y <= y_cord) && (y_cord < allButtons["test1Button"].getPosition().y + 64))
	{
		test1 = true;
		test2 = false;
		test3 = false;
		gameOver = false;
	}
	else if ((allButtons["test2Button"].getPosition().x <= x_cord) && (x_cord < allButtons["test2Button"].getPosition().x + 64) && (allButtons["test2Button"].getPosition().y <= y_cord) && (y_cord < allButtons["test2Button"].getPosition().y + 64))
	{
		test2 = true;
		test1 = false;
		test3 = false;
		gameOver = false;
	}
	else if((allButtons["test3Button"].getPosition().x <= x_cord) && (x_cord < allButtons["test3Button"].getPosition().x + 64) && (allButtons["test3Button"].getPosition().y <= y_cord) && (y_cord < allButtons["test3Button"].getPosition().y + 64))
	{
		test3 = true;
		test1 = false;
		test2 = false;
		gameOver = false;
	}
}

// Draws all the buttons on the board.
void Board::drawButtons(sf::RenderWindow& window)
{
	int windowHeight = (ROWS * 32) + 100;
	sf::Vector2f facePosition((window.getSize().x / 2) - 32, (windowHeight - 100));
	sf::Sprite faceButton = drawSmileyFaceButton(facePosition);
	window.draw(faceButton);
	
	sf::Vector2f debugPosition((window.getSize().x / 2) + 96, (windowHeight - 100));
	sf::Sprite debugButton = drawDebugButton(debugPosition);
	window.draw(debugButton);

	sf::Vector2f test1Position((window.getSize().x / 2)+ 160, (windowHeight - 100));
	sf::Sprite test1Button = drawTest1Button(test1Position);
	window.draw(test1Button);
	
	sf::Vector2f test2Position((window.getSize().x / 2) + 224, (windowHeight - 100));
	sf::Sprite test2Button = drawTest2Button(test2Position);
	window.draw(test2Button);
	
	sf::Vector2f test3Position((window.getSize().x / 2) + 288, (windowHeight - 100));
	sf::Sprite test3Button = drawTest3Button(test3Position);
	window.draw(test3Button);

}

// Draws all the digits on the board.
void Board::drawDigits(sf::RenderWindow& window)
{
	if (flagCounter < 0)
	{
		sf::Vector2f negativeDigitsPosition(0, ROWS * 32);
		sf::Sprite negativeDigits = drawNegativeDigits(negativeDigitsPosition);
		window.draw(negativeDigits);
		flagCounter *= -1;

		int ones = flagCounter % 10;
		int tens = flagCounter / 10;
		int hundreds = flagCounter / 100;

		if (tens == 10)
			tens = 0;

		if (hundreds == 10)
			hundreds = 0;

		sf::Vector2f onesDigitsPosition(21 * 3, ROWS * 32);
		sf::Sprite onesDigits = drawOnesDigits(onesDigitsPosition, ones);
		window.draw(onesDigits);

		sf::Vector2f tensDigitsPosition(21 * 2, ROWS * 32);
		sf::Sprite tensDigits = drawTensDigits(tensDigitsPosition, tens);
		window.draw(tensDigits);

		sf::Vector2f hundredsDigitsPosition(21, ROWS * 32);
		sf::Sprite hundredsDigits = drawHundredsDigits(hundredsDigitsPosition, hundreds);
		window.draw(hundredsDigits);

		flagCounter *= -1;
	}
	else if (flagCounter >= 0)
	{
		int ones = flagCounter % 10;
		int tens = flagCounter / 10;
		int hundreds = flagCounter / 100;

		if (tens == 10)
			tens = 0;

		if (hundreds == 10)
			hundreds = 0;

		sf::Vector2f onesDigitsPosition(21 * 2, ROWS * 32);
		sf::Sprite onesDigits = drawOnesDigits(onesDigitsPosition, ones);
		window.draw(onesDigits);

		sf::Vector2f tensDigitsPosition(21, ROWS * 32);
		sf::Sprite tensDigits = drawTensDigits(tensDigitsPosition, tens);
		window.draw(tensDigits);

		sf::Vector2f hundredsDigitsPosition(0, ROWS * 32);
		sf::Sprite hundredsDigits = drawHundredsDigits(hundredsDigitsPosition, hundreds);
		window.draw(hundredsDigits);
	}
}

// Creates a texture rectangle to adjust the digits sprite.
void Board::changeDigits(int ones, int tens, int hundreds)
{
	onesDigits.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
	onesDigits.setPosition(3 * 21, ROWS * 32);

	tensDigits.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
	tensDigits.setPosition(2 * 21, ROWS * 32);

	hundredsDigits.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
	hundredsDigits.setPosition(21, ROWS * 32);

}