#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "Random.h"
#include "Tile.h"
#include "Board.h"
#include "Button.h"
using namespace std;

// Used to read data from the config file.
vector<int> readData(const string& filename)
{
	ifstream file(filename);
	vector<int> configData;
	if (file.is_open())
	{
		string line = "";
		while (getline(file, line))
		{
			string tempNumber = "";
			unsigned int data = 0;
			
			stringstream inputString(line);
			getline(inputString, tempNumber); // temp string for data
			data = stoi(tempNumber);

			configData.push_back(data);
		}
	}
	return configData;
}

int main()
{
	vector<int> config = readData("boards/config.cfg");
	unsigned int COLUMNS = 0;
	unsigned int ROWS = 0;
	unsigned int MINES = 0;

	COLUMNS = config[0];
	ROWS = config[1];
	MINES = config[2];

	Board gameBoard(COLUMNS, ROWS, MINES);

	int windowWidth = COLUMNS * 32;
	int windowHeight = (ROWS * 32) + 100;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

			// SFML mouseButton.button function registers multiple left mouse clicks (due to the FPS of the window)
			// "Locking" the left and right mouse click events will allow us to register only one input at a time.
			bool lockLeftClick = false;
			bool lockRightClick = false;
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left && lockLeftClick != true)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					gameBoard.revealBoardTile(mousePosition.x, mousePosition.y);
					gameBoard.clickButtons(mousePosition.x, mousePosition.y);
					lockLeftClick = true;
				}

				if (event.mouseButton.button == sf::Mouse::Right && lockRightClick != true)
				{
					sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
					gameBoard.flagTile(mousePosition.x, mousePosition.y);
					lockRightClick = true;
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					lockLeftClick = false;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					lockRightClick = false;
				}
			}
        }
        window.clear(sf::Color::White);
		gameBoard.drawButtons(window);
		gameBoard.drawDigits(window);
		gameBoard.checkGameLose(window);
		gameBoard.checkGameWin(window);
		
		// Test button 1 (with debugMode ON)
		if (gameBoard.test1 == true && gameBoard.test2 == false && gameBoard.test3 == false && gameBoard.gameOver == false && gameBoard.debugMode == true)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard1.brd");
			gameBoard.showAllMines();
			gameBoard.debugMode = true;

			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Test button 1 (with debugMode OFF)
		else if (gameBoard.test1 == true && gameBoard.test2 == false && gameBoard.test3 == false && gameBoard.gameOver == false)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard1.brd");
			
			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Test button 2 (with debugMode ON)
		else if (gameBoard.test1 == false && gameBoard.test2 == true && gameBoard.test3 == false && gameBoard.gameOver == false && gameBoard.debugMode == true)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard2.brd");
			gameBoard.showAllMines();
			gameBoard.debugMode = true;

			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Test button 2 (with debugMode OFF)
		else if (gameBoard.test1 == false && gameBoard.test2 == true && gameBoard.test3 == false && gameBoard.gameOver == false)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard2.brd");

			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Test button 3 (with debugMode ON)
		else if (gameBoard.test1 == false && gameBoard.test2 == false && gameBoard.test3 == true && gameBoard.gameOver == false && gameBoard.debugMode == true)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard3.brd");
			gameBoard.showAllMines();
			gameBoard.debugMode = true;

			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Test button 3 (with debugMode OFF)
		else if (gameBoard.test1 == false && gameBoard.test2 == false && gameBoard.test3 == true && gameBoard.gameOver == false)
		{
			gameBoard = gameBoard.restartBoard();
			gameBoard.testBoards(gameBoard, "boards/testboard3.brd");

			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Resets the board when the face button is clicked and debugMode is ON.
		else if (gameBoard.gameOver == true && gameBoard.debugMode == true && gameBoard.test1 == false && gameBoard.test2 == false && gameBoard.test3 == false)
		{
			gameBoard.setBoardMineCount(MINES);
			gameBoard = gameBoard.restartBoard();
			gameBoard.showAllMines();
			gameBoard.debugMode = true;
			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// Resets the board when the face button is clicked, but debugMode is OFF.
		else if (gameBoard.gameOver == true && gameBoard.debugMode == false && gameBoard.test1 == false && gameBoard.test2 == false && gameBoard.test3 == false)
		{
			gameBoard.setBoardMineCount(MINES);
			gameBoard = gameBoard.restartBoard();
			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
		// All other instances.
		else if (gameBoard.gameOver == false)
		{
			for (unsigned int i = 0; i < ROWS; i++)
			{
				for (unsigned int j = 0; j < COLUMNS; j++)
				{
					window.draw(gameBoard.board[i][j].getTileSprite());
					window.draw(gameBoard.board[i][j].getFlagSprite());
					window.draw(gameBoard.board[i][j].getMineSprite());
					window.draw(gameBoard.board[i][j].getNumberSprite());
				}
			}
		}
        window.display();
    }
    // Clear out any textures before the program ends
    TextureManager::Clear();
    return 0;
}